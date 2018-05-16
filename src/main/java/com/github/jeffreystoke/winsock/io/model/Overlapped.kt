package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.struct.Socket
import com.github.jeffreystoke.winsock.io.struct.Struct
import com.github.jeffreystoke.winsock.io.struct.WSAOverlapped

class Overlapped : Struct() {

    fun getOverlappedResult(socket: Socket, overlapped: WSAOverlapped, bytes: Int, wait: Boolean, flag: Long): Boolean {
        return WinSock._wsa_get_overlapped_result(socket.getPtr(), overlapped.getPtr(), bytes, wait, flag)
    }
}