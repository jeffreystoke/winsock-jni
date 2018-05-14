package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.internal.Pointer
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.isNull

abstract class Struct {
    protected var _ptr: Pointer = 0

    fun getPtr(): Pointer {
        return _ptr
    }

    fun destroy() {
        if (_ptr.isNull()) {
            return
        }

        WinSock._free(_ptr)
    }
}