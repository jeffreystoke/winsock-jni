/*
 * Copyright (c) 2018 JeffreyStoke (https://github.com/jeffreystoke)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.constant.NetEvent
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.struct.WSAEvent
import com.github.jeffreystoke.winsock.io.util.mergedEvent

class EventSelectModel {

    /**
     * 开始一次 WSAEventSelect
     *
     * @param socket 与 WSAEvent 事件绑定 的 Socket
     * @param event WSAEvent 事件对象
     * @param caredNetEvents 关注的网络事件
     *
     * @return Int
     */
    fun run(event: WSAEvent, vararg caredNetEvents: NetEvent): Int =
            WinSock._wsa_event_select(event.socket.getPtr(), event.getPtr(), caredNetEvents.mergedEvent())

    /**
     * 等待多个事件， 当一个发生时返回
     *
     * @param events WSAEvent 集合
     * @param waitTimeout 等待超时
     *
     * @return WSAEvent 发生事件的对象
     */
    fun waitForMultipleEvents(events: List<WSAEvent>, waitTimeout: Int): WSAEvent {
        val index = WinSock._wsa_wait_for_multiple_events(events.size,
                LongArray(events.size, { i -> events[i].getPtr() }),
                false, waitTimeout, false)
        return events[index - WinSock.WSA_WAIT_EVENT_0]
    }
}