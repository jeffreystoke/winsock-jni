package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.constant.*
import com.github.jeffreystoke.winsock.io.internal.Pointer
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.isNull
import java.io.IOException

class Socket(addressFamily: AddressFamily = AddressFamily.Internet,
             type: SocketType = SocketType.Stream,
             protocol: ProtocolType = ProtocolType.TCP) : Struct() {

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
//        WinSock._ioctlsocket(_ptr)
    }

    fun bind(address: String, port: Int) {
        WinSock._bind(_ptr, address, port)
    }

    fun listen(backlog: Int) {
        WinSock._listen(_ptr, backlog)
    }

    fun accept(): Socket {
        return Socket(WinSock._accept(_ptr))
    }

    @Throws(IOException::class)
    fun connect(address: String, port: Int) {
        val ret = WinSock._connect(_ptr, address, port)
        if (ret == SocketError.Error.value) {
            throw IOException("调用 connect 失败")
        }
    }

    @Throws(IOException::class)
    fun recv(buf: ByteArray, flag: Int = 0): Int {
        val ret = WinSock._recv(_ptr, buf, flag)
        if (ret == SocketError.Error.value) {
            throw IOException("调用 recv 失败")
        }

        return ret
    }

    @Throws(IOException::class)
    fun send(buf: ByteArray, flag: Int = 0): Int {
        val ret = WinSock._send(_ptr, buf, flag)
        if (ret == SocketError.Error.value) {
            throw IOException("调用 send 失败")
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
        if (ret == SocketError.Error.value) {
            throw IOException("调用 getsockopt 失败")
        }
        return buf
    }

    @Throws(IOException::class)
    fun setOption(optionName: SocketOption, optionValue: ByteArray) {
        val ret = WinSock._setsockopt(_ptr, 0xffff, optionName.value, optionValue)
        if (ret == SocketError.Error.value) {
            throw IOException("调用 setsockopt 失败")
        }
    }
}