package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.struct.Struct
import com.github.jeffreystoke.winsock.io.struct.WSAEvent
import com.github.jeffreystoke.winsock.io.struct.WSAOverlapped

class OverlappedModel : Struct() {


    /**
     * 等待多个事件， 当一个发生时返回
     *
     * @param events        WSAEvent 集合
     * @param waitTimeout   等待超时
     *
     * @return WSAEvent     发生事件的对象
     */
    fun waitForMultipleEvents(events: Array<WSAEvent>, waitTimeout: Int): WSAEvent {
        val index = WinSock._wsa_wait_for_multiple_events(events.size,
                LongArray(events.size, { i -> events[i].getPtr() }),
                false, waitTimeout, false)
        return events[index - WinSock.WSA_WAIT_EVENT_0]
    }

    /**
     * 返回重叠IO操作结果
     *
     * @param overlapped    WSAOverlapped 结构, 包含 WSAEvent,
     *                      WSAEvent 内部需要是 WSASocket 对象
     * @param wait          等待重叠操作完成
     * @param flag          完成状态的附加标志
     *
     * @return Int          实际传输数据量, -1 表示出错
     */
    fun getOverlappedResult(overlapped: WSAOverlapped, wait: Boolean, flag: Long): Int {
        return WinSock._wsa_get_overlapped_result(overlapped.wsaEvent.socket.getPtr(), overlapped.getPtr(), wait, flag)
    }

}