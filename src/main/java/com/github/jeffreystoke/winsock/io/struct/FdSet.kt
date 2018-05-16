package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.internal.WinSock._add_fd
import com.github.jeffreystoke.winsock.io.internal.WinSock._create_fd_set
import com.github.jeffreystoke.winsock.io.internal.WinSock._get_set_fd
import com.github.jeffreystoke.winsock.io.internal.WinSock._remove_fd
import com.github.jeffreystoke.winsock.io.util.isNull

class FdSet(socketList: List<Socket> = emptyList()) : Struct() {

    init {
        if (socketList.isNotEmpty()) {
            socketList.forEach { s ->
                add(s)
            }
        }
    }

    fun add(socket: Socket) {
        if (_ptr.isNull()) {
            _ptr = _create_fd_set()
            if (_ptr.isNull()) {
                throw RuntimeException("无法创建 FD_SET")
            }
        }

        _add_fd(_ptr, socket.getPtr())
    }

    fun remove(socket: Socket) {
        if (_ptr.isNull()) {
            return
        }

        _remove_fd(_ptr, socket.getPtr())
    }

    fun getSetFd(): Socket? {
        if (_ptr.isNull()) {
            return null
        }

        return Socket(_get_set_fd(_ptr))
    }
}