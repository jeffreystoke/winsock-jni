package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.Pointer
import com.github.jeffreystoke.winsock.io.util.isNull

abstract class Struct {
    protected var _ptr: Pointer = 0

    open fun getPtr(): Pointer {
        return _ptr
    }

    open fun destroy() {
        if (_ptr.isNull()) {
            return
        }

        WinSock._free(_ptr)
    }
}