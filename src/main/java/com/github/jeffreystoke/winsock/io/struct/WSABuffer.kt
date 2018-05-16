package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.isNull

class WSABuffer(val size: Int = 256) : Struct() {

    init {
        _ptr = WinSock._create_wsa_buf(size)
        if (_ptr.isNull()) {
            throw RuntimeException("创建 WSABuf 失败")
        }
    }

    override fun destroy() {
        if (_ptr.isNull()) {
            return
        }

        WinSock._destroy_wsa_buf(_ptr)
    }
}