package com.github.jeffreystoke.winsock.io.util

import com.github.jeffreystoke.winsock.io.constant.NetEvent
import com.github.jeffreystoke.winsock.io.internal.WinSock

typealias Pointer = Long

fun Pointer.isNull(): Boolean {
    return this < 1
}

fun Array<NetEvent>.mergedEvent(): Long {
    var event = 0L
    this.forEach { e ->
        event = event.or(e.value)
    }
    return event
}

fun wsaCleanup() = WinSock._wsa_cleanup()

fun wsaGetLastError() = WinSock._wsa_get_last_error()