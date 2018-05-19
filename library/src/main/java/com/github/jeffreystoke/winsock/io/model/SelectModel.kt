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
import com.github.jeffreystoke.winsock.io.struct.FdSet
import com.github.jeffreystoke.winsock.io.struct.Socket

class SelectModel(private val readFdSet: FdSet = FdSet(),
                  private val writeFdSet: FdSet = FdSet(),
                  private val exceptionFdSet: FdSet = FdSet()) {

    /**
     * 开始一次 select
     *
     * @param timeout 等待超时时间
     */
    fun run(timeout: Int): Int {
        return WinSock._select(readFdSet.getPtr(), writeFdSet.getPtr(), exceptionFdSet.getPtr(), timeout)
    }

    /**
     * 添加将监听读(接收)事件的 Socket
     *
     * @param s Socket
     */
    fun addReadSocket(s: Socket) {
        readFdSet.add(s)
    }

    /**
     * 添加将监听写(发送)事件的 Socket
     *
     * @param s Socket
     */
    fun addWriteSocket(s: Socket) {
        writeFdSet.add(s)
    }

    /**
     * 添加将监听出错事件的 Socket
     *
     * @param s Socket
     */
    fun addExceptionSocket(s: Socket) {
        exceptionFdSet.add(s)
    }

    /**
     * 移除监听读(接收)事件的 Socket, Socket 本身不受影响
     *
     * @param s Socket
     */
    fun removeReadSocket(s: Socket) {
        readFdSet.remove(s)
    }

    /**
     * 移除监听写(发送)事件的 Socket, Socket 本身不受影响
     *
     * @param s Socket
     */
    fun removeWriteSocket(s: Socket) {
        writeFdSet.remove(s)
    }

    /**
     * 移除监听出错事件的 Socket, Socket 本身不受影响
     *
     * @param s Socket
     */
    fun removeExceptionSocket(s: Socket) {
        exceptionFdSet.remove(s)
    }

    /**
     * 获取发生读(接收)事件的 Socket
     *
     * @return Socket
     */
    fun getReadSetSocket(): Socket? {
        return readFdSet.getSetFd()
    }

    /**
     * 获取发生写(发送)事件的 Socket
     *
     * @return Socket
     */
    fun getWriteSetSocket(): Socket? {
        return writeFdSet.getSetFd()
    }

    /**
     * 获取发生出错事件的 Socket
     *
     * @return socket
     */
    fun getExceptionSetSocket(): Socket? {
        return exceptionFdSet.getSetFd()
    }

    /**
     * 清空内部所有 Socket
     */
    fun clear() {
        readFdSet.destroy()
        writeFdSet.destroy()
        exceptionFdSet.destroy()
    }
}