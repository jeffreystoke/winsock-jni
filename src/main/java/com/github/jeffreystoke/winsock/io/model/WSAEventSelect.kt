package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.constant.NetEvent
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.struct.Socket
import com.github.jeffreystoke.winsock.io.struct.WSAEvent
import com.github.jeffreystoke.winsock.io.util.mergedEvent

class WSAEventSelect {

    fun select(socket: Socket, event: WSAEvent, caredNetEvents: Array<NetEvent>): Int =
            WinSock._wsa_event_select(socket.getPtr(), event.getPtr(), caredNetEvents.mergedEvent())

    // 返回值需要减去 WSA_WAIT_EVENT_0 才是数组索引
    fun waitForMultipleEvents(events: List<WSAEvent>, waitAll: Boolean, waitTimeout: Int): Int =
            WinSock._wsa_wait_for_multiple_events(events.size, LongArray(events.size, { i -> events[i].getPtr() }), waitAll, waitTimeout, false)

}