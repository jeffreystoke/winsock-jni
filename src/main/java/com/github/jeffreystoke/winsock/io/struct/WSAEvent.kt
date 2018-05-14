package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.constant.SocketError
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.isNull
import java.io.IOException
import java.nio.ByteBuffer

class WSAEvent : Struct() {

    init {
        _ptr = WinSock._wsaCreateEvent()
        if (_ptr.isNull()) {
            throw RuntimeException("无法创建 WSAEvent 对象")
        }
    }

    @Throws(IOException::class)
    fun reset() {
        if (!WinSock._wsaResetEvent(_ptr)) throw IOException("执行 WSARestEvent 失败")
    }

    @Throws(IOException::class)
    fun close() {
        if (!WinSock._wsaCloseEvent(_ptr)) throw IOException("执行 WSACloseEvent 失败")
    }

    @Throws(IOException::class)
    fun getNetEvent(socket: Socket): Long {
        val buf = ByteArray(8)
        if (WinSock._wsaEnumNetworkEvents(socket.getPtr(), _ptr, buf) == SocketError.Error.value) {
            throw IOException("无法调用 WSAEnumNetworkEvents")
        }

        return ByteBuffer.wrap(buf).getLong(0)
    }
}