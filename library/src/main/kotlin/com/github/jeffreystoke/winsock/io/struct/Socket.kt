/*
 * Copyright (c) 2018 JeffreyStoke (https://github.com/jeffreystoke)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.constant.*
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.Pointer
import com.github.jeffreystoke.winsock.io.util.isNull
import java.io.IOException
import java.nio.ByteBuffer

open class Socket(addressFamily: AddressFamily = AddressFamily.Internet,
                  type: SocketType = SocketType.Stream,
                  protocol: ProtocolType = ProtocolType.TCP) : Struct() {

    var address: String = ""
    var port: Int = 0

    internal constructor(socket: Pointer) : this() {
        _ptr = socket
    }

    init {
        _ptr = WinSock._socket(addressFamily.value, type.value, protocol.value)
        if (_ptr.isNull()) {
            throw RuntimeException("无法创建 socket 对象")
        }
    }

    fun setNonBlock(enable: Boolean) {
        WinSock._ioctlsocket(_ptr, enable)
    }

    fun bind(address: String, port: Int) {
        WinSock._bind(_ptr, address, port)
    }

    fun listen() {
        listen(0)
    }

    fun listen(backlog: Int = 0) {
        WinSock._listen(_ptr, backlog)
    }

    @Throws(IOException::class)
    fun accept(): Socket {
        val addressBuf = ByteArray(256)
        val portBuf = ByteArray(2)
        val socket = WinSock._accept(_ptr, addressBuf, portBuf)
        if (socket == SocketError.INVALID_SOCKET.value) {
            throw IOException("调用 Accept 失败")
        }

        return Socket(socket).let { s ->
            s.address = String(addressBuf)
            s.port = ByteBuffer.wrap(portBuf).short.toInt()
            s
        }
    }

    @Throws(IOException::class)
    fun connect(address: String, port: Int) {
        val ret = WinSock._connect(_ptr, address, port)
        if (ret == SocketError.Error.value.toInt()) {
            throw IOException("调用 connect 失败")
        }
    }

    @Throws(IOException::class)
    fun recv(): ByteArray {
        return recv(buf = ByteArray(1024))
    }

    @Throws(IOException::class)
    fun recv(buf: ByteArray = ByteArray(1024), flag: Int = 0): ByteArray {
        val ret = WinSock._recv(_ptr, buf, flag)
        if (ret == SocketError.Error.value.toInt()) {
            throw IOException("调用 recv 失败")
        }

        return buf.copyOf(ret)
    }

    @Throws(IOException::class)
    fun recvFrom(flag: Int = 0): UDPPacket {
        val udpBuf = ByteArray(10)
        val addressBuf = ByteArray(65536)
        val portBuf = ByteArray(2)
        val ret = WinSock._recv_from(_ptr, udpBuf, flag, addressBuf, portBuf)

        if (ret == SocketError.Error.value.toInt()) {
            throw IOException("调用 send 失败")
        }

        return UDPPacket(String(addressBuf), ByteBuffer.wrap(portBuf).short.toInt(), udpBuf.copyOf(ret))
    }

    @Throws(IOException::class)
    fun send(data: ByteArray): Int {
        return send(data, 0)
    }

    @Throws(IOException::class)
    fun send(data: ByteArray, flag: Int = 0): Int {
        val ret = WinSock._send(_ptr, data, flag)
        if (ret == SocketError.Error.value.toInt()) {
            throw IOException("调用 send 失败")
        }

        return ret
    }

    @Throws(IOException::class)
    fun sendTo(udpPacket: UDPPacket, flag: Int = 0): Int {
        val ret = WinSock._send_to(_ptr, udpPacket.data, flag, udpPacket.address, udpPacket.port)
        if (ret == SocketError.Error.value.toInt()) {
            throw IOException("调用 sendTo 失败")
        }

        return ret
    }

    fun shutdown(how: ShutdownOption = ShutdownOption.Both) {
        WinSock._shutdown(_ptr, how.value)
    }

    @Throws(IOException::class)
    fun close() {
        if (WinSock._closesocket(_ptr) == WSAError.WSAENOTSOCK.value) {
            throw IOException("无法关闭 socket, 正在使用中")
        }
    }

    @Throws(IOException::class)
    fun getOption(optionName: SocketOption): ByteArray {
        val buf = ByteArray(256)
        val ret = WinSock._getsockopt(_ptr, 0xffff, optionName.value, buf)
        if (ret == SocketError.Error.value.toInt()) {
            throw IOException("调用 getsockopt 失败")
        }
        return buf
    }

    @Throws(IOException::class)
    fun setOption(optionName: SocketOption, optionValue: ByteArray) {
        val ret = WinSock._setsockopt(_ptr, 0xffff, optionName.value, optionValue)
        if (ret == SocketError.Error.value.toInt()) {
            throw IOException("调用 setsockopt 失败")
        }
    }
}