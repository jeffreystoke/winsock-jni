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

package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.constant.NetEvent
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.isNull
import java.io.IOException
import java.nio.ByteBuffer


class WSAEvent(val socket: Socket) : Struct() {

    init {
        _ptr = WinSock._wsa_create_event()
        if (_ptr.isNull()) {
            throw RuntimeException("无法创建 WSAEvent 对象")
        }
    }

    /**
     * 将状态设置为未传信
     */
    @Throws(IOException::class)
    fun reset() {
        if (!WinSock._wsa_reset_event(_ptr)) throw IOException("执行 WSARestEvent 失败")
    }

    /**
     * 关闭事件，不再有效
     */
    @Throws(IOException::class)
    fun close() {
        if (!WinSock._wsa_close_event(_ptr)) throw IOException("执行 WSACloseEvent 失败")
    }

    /**
     * 获取发生的网络事件
     */
    @Throws(IOException::class)
    fun getNetEvent(): NetEvent {
        val bufForLong = ByteArray(8)
        val bufForInt = ByteArray(40)
        val ret = WinSock._wsa_enum_network_events(socket.getPtr(), _ptr, bufForLong, bufForInt)
        if (ret != 0) {
            throw IOException("调用 WSAEnumNetworkEvents 失败")
        }

        val netEvent = ByteBuffer.wrap(bufForLong).long
        val netErrors = ByteBuffer.wrap(bufForInt)
        val netErrorArray = Array(10, { 0 })
        for (i in 0..40 step 4) {
            netErrorArray[i / 4] = netErrors.getInt(i)
        }

        when (netEvent) {
            NetEvent.FD_ACCEPT.value -> {
                val errCode = netErrorArray[NetEvent.FD_ACCEPT_BIT.value.toInt()]
                if (errCode != 0) {
                    throw IOException("Accept 出错: $errCode")
                }
                return NetEvent.FD_ACCEPT
            }
            NetEvent.FD_READ.value -> {
                val errCode = netErrorArray[NetEvent.FD_READ_BIT.value.toInt()]
                if (errCode != 0) {
                    throw IOException("Read 出错: $errCode")
                }
                return NetEvent.FD_READ
            }
            NetEvent.FD_WRITE.value -> {
                val errCode = netErrorArray[NetEvent.FD_WRITE_BIT.value.toInt()]
                if (errCode != 0) {
                    throw IOException("Write 出错: $errCode")
                }
                return NetEvent.FD_WRITE
            }
            NetEvent.FD_CLOSE.value -> {
                val errCode = netErrorArray[NetEvent.FD_CLOSE_BIT.value.toInt()]
                if (errCode != 0) {
                    throw IOException("Close 出错: $errCode")
                }
                return NetEvent.FD_CLOSE
            }
            NetEvent.FD_CONNECT.value -> {
                val errCode = netErrorArray[NetEvent.FD_CONNECT_BIT.value.toInt()]
                if (errCode != 0) {
                    throw IOException("Connect 出错: $errCode")
                }
                return NetEvent.FD_CONNECT
            }
            NetEvent.FD_ADDRESS_LIST_CHANGE.value -> {
                val errCode = netErrorArray[NetEvent.FD_ADDRESS_LIST_CHANGE_BIT.value.toInt()]
                if (errCode != 0) {
                    throw IOException("Address list change 出错: $errCode")
                }
                return NetEvent.FD_ADDRESS_LIST_CHANGE
            }
            NetEvent.FD_GROUP_QOS.value -> {
                val errCode = netErrorArray[NetEvent.FD_GROUP_QOS_BIT.value.toInt()]
                if (errCode != 0) {
                    throw IOException("Group QoS 出错: $errCode")
                }
                return NetEvent.FD_GROUP_QOS
            }
            NetEvent.FD_OOB.value -> {
                val errCode = netErrorArray[NetEvent.FD_OOB_BIT.value.toInt()]
                if (errCode != 0) {
                    throw IOException("OOB 出错: $errCode")
                }
                return NetEvent.FD_OOB
            }
            NetEvent.FD_QOS.value -> {
                val errCode = netErrorArray[NetEvent.FD_QOS_BIT.value.toInt()]
                if (errCode != 0) {
                    throw IOException("QoS 出错: $errCode")
                }
                return NetEvent.FD_QOS
            }
            NetEvent.FD_ROUTING_INTERFACE_CHANGE.value -> {
                val errCode = netErrorArray[NetEvent.FD_ROUTING_INTERFACE_CHANGE_BIT.value.toInt()]
                if (errCode != 0) {
                    throw IOException("Routine Interface change 出错: $errCode")
                }
                return NetEvent.FD_ROUTING_INTERFACE_CHANGE
            }

        }

        throw IOException("非法网络事件")
    }
}