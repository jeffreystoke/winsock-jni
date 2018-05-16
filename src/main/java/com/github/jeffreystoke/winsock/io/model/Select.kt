package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.struct.FdSet
import com.github.jeffreystoke.winsock.io.struct.Socket

class Select(private val readFdSet: FdSet = FdSet(),
             private val writeFdSet: FdSet = FdSet(),
             private val exceptionFdSet: FdSet = FdSet()) {

    fun addReadFd(s: Socket) {
        readFdSet.add(s)
    }

    fun addWriteFd(s: Socket) {
        writeFdSet.add(s)
    }

    fun addExceptionFd(s: Socket) {
        exceptionFdSet.add(s)
    }

    fun removeReadFd(s: Socket) {
        readFdSet.remove(s)
    }

    fun removeWriteFd(s: Socket) {
        writeFdSet.remove(s)
    }

    fun removeExceptionFd(s: Socket) {
        exceptionFdSet.remove(s)
    }

    fun getReadSetFd(): Socket? {
        return readFdSet.getSetFd()
    }

    fun getWriteSetFd(): Socket? {
        return writeFdSet.getSetFd()
    }

    fun getExceptionSetFd(): Socket? {
        return exceptionFdSet.getSetFd()
    }

    fun select(timeout: Int): Int {
        return WinSock._select(readFdSet.getPtr(), writeFdSet.getPtr(), exceptionFdSet.getPtr(), timeout)
    }

    fun destroy() {
        readFdSet.destroy()
        writeFdSet.destroy()
        exceptionFdSet.destroy()
    }
}