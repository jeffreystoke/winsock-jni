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
import com.github.jeffreystoke.winsock.io.struct.Socket
import java.nio.ByteBuffer
import java.nio.ByteOrder

class SelectModel(private val reads: MutableList<Socket> = ArrayList(),
                  private val writes: MutableList<Socket> = ArrayList(),
                  private val exceptions: MutableList<Socket> = ArrayList()) {

    /**
     * 开始一次 select
     *
     * @param timeout 等待超时时间
     */
    @Throws(RuntimeException::class)
    fun select(timeout: Int): Socket? {
        val netEventBuf = ByteArray(8)
        val ret = WinSock._select(LongArray(reads.size, { reads[it].getPtr() }),
                LongArray(writes.size, { writes[it].getPtr() }),
                LongArray(exceptions.size, { exceptions[it].getPtr() }), timeout, netEventBuf)
        if (ret < 1) {
            throw RuntimeException("select failed $ret")
        }

        val netEvent = ByteBuffer.wrap(netEventBuf).order(ByteOrder.LITTLE_ENDIAN).long.and(0xFF)
        val event = when (netEvent) {
            NetEvent.FD_READ.value -> NetEvent.FD_READ
            NetEvent.FD_WRITE.value -> NetEvent.FD_WRITE
            NetEvent.FD_CLOSE.value -> NetEvent.FD_CLOSE
            else -> {
                throw RuntimeException("unknown net event")
            }
        }

        return Socket.getSocket(ret)?.let {
            it.selectEvent = event
            it
        }
    }

    /**
     * 添加将监听读(接收)事件的 Socket
     *
     * @param s Socket
     */
    fun addReadSocket(s: Socket) {
        reads.add(s)
    }

    /**
     * 添加将监听写(发送)事件的 Socket
     *
     * @param s Socket
     */
    fun addWriteSocket(s: Socket) {
        writes.add(s)
    }

    /**
     * 添加将监听出错事件的 Socket
     *
     * @param s Socket
     */
    fun addExceptionSocket(s: Socket) {
        exceptions.add(s)
    }

    /**
     * 移除监听读(接收)事件的 Socket, Socket 本身不受影响
     *
     * @param s Socket
     */
    fun removeReadSocket(s: Socket) {
        reads.remove(s)
    }

    /**
     * 移除监听写(发送)事件的 Socket, Socket 本身不受影响
     *
     * @param s Socket
     */
    fun removeWriteSocket(s: Socket) {
        writes.remove(s)
    }

    /**
     * 移除监听出错事件的 Socket, Socket 本身不受影响
     *
     * @param s Socket
     */
    fun removeExceptionSocket(s: Socket) {
        exceptions.remove(s)
    }
}