package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.constant.AddressFamily
import com.github.jeffreystoke.winsock.io.constant.ProtocolType
import com.github.jeffreystoke.winsock.io.constant.SocketFlag
import com.github.jeffreystoke.winsock.io.constant.SocketType
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.isNull
import java.io.IOException

class WSASocket(addressFamily: AddressFamily = AddressFamily.Internet,
                type: SocketType = SocketType.Stream,
                protocol: ProtocolType = ProtocolType.TCP,
                flag: SocketFlag = SocketFlag.WSA_FLAG_OVERLAPPED) : Socket() {

    init {
        _ptr = WinSock._wsa_socket(addressFamily.value, type.value, protocol.value, flag.value)
        if (_ptr.isNull()) {
            throw RuntimeException("无发创建 WSASocket")
        }
    }

    @Throws(IOException::class)
    fun wsaRecv(buf: ByteArray, overlapped: WSAOverlapped): Int {
        return WinSock._wsa_recv(_ptr, buf, overlapped.getPtr())
    }

    @Throws(IOException::class)
    fun wsaSend(data: ByteArray, overlapped: WSAOverlapped): Int {
        return WinSock._wsa_send(_ptr, data, overlapped.getPtr())
    }
}