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