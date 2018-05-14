package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.internal.WinSock._addFd
import com.github.jeffreystoke.winsock.io.internal.WinSock._createFdSet
import com.github.jeffreystoke.winsock.io.internal.WinSock._getSetFd
import com.github.jeffreystoke.winsock.io.internal.WinSock._removeFd
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
            _ptr = _createFdSet()
            if (_ptr.isNull()) {
                throw RuntimeException("无法创建 FD_SET")
            }
        }

        _addFd(_ptr, socket.getPtr())
    }

    fun remove(socket: Socket) {
        if (_ptr.isNull()) {
            return
        }

        _removeFd(_ptr, socket.getPtr())
    }

    fun getSetFd(): Socket? {
        if (_ptr.isNull()) {
            return null
        }

        return Socket(_getSetFd(_ptr))
    }
}