package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.isNull

class WSAOverlapped(internal: Int,
                    internalHigh: Int,
                    offset: Int,
                    offsetHigh: Int,
                    val wsaEvent: WSAEvent) : Struct() {

    init {
        _ptr = WinSock._create_wsa_overlapped(internal, internalHigh, offset, offsetHigh, wsaEvent.getPtr())
        if (_ptr.isNull()) {
            throw RuntimeException("无法创建 WSAOverlapped 结构")
        }
    }

}