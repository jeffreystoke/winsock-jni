package com.github.jeffreystoke.winsock.io.util

import com.github.jeffreystoke.winsock.io.constant.NetEvent

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