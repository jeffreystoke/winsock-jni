package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.constant.NetEvent
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.struct.Socket
import com.github.jeffreystoke.winsock.io.struct.WSAEvent
import com.github.jeffreystoke.winsock.io.util.mergedResult

object WSAEventSelect {

    fun start(socket: Socket, event: WSAEvent, caredNetEvents: Array<NetEvent>): Int =
            WinSock._wsaEventSelect(socket.getPtr(), event.getPtr(), caredNetEvents.mergedResult())

    // 返回值需要减去 WSA_WAIT_EVENT_0 才是数组索引
    fun waitForMultipleEvents(events: List<WSAEvent>, waitAll: Boolean, waitTimeout: Int): Int =
            WinSock._wsaWaitForMultipleEvents(events.size, Array(events.size, { i -> events[i].getPtr() }), waitAll, waitTimeout, false)


}