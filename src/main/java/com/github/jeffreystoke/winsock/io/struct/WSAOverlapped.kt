package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.internal.Pointer
import com.github.jeffreystoke.winsock.io.util.isNull

class WSAOverlapped(internal: Int, internalHigh: Int, offset: Int, offsetHigh: Int, wsaEvent: WSAEvent) {

    private var _ptr: Pointer = 0

    init {
        _ptr = _create_wsa_overlapped(internal, internalHigh, offset, offsetHigh, wsaEvent)
        if (_ptr.isNull()) {
            throw RuntimeException("无法创建 WSAOverlapped 结构")
        }
    }

    fun getAddress(): Pointer {
        return _ptr
    }

    companion object {
        external fun _create_wsa_overlapped(internal: Int, internalHigh: Int, offset: Int, offsetHigh: Int, wsaEvent: WSAEvent): Pointer
    }
}