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

package com.github.jeffreystoke.winsock.io.constant

enum class NetEvent(val value: Long) {
    FD_READ_BIT(0L),
    FD_READ(1L.shl(FD_READ_BIT.value.toInt())),
    FD_WRITE_BIT(1),
    FD_WRITE(1L.shl(FD_WRITE_BIT.value.toInt())),
    FD_OOB_BIT(2),
    FD_OOB(1L.shl(FD_OOB_BIT.value.toInt())),
    FD_ACCEPT_BIT(3),
    FD_ACCEPT(1L.shl(FD_ACCEPT_BIT.value.toInt())),
    FD_CONNECT_BIT(4),
    FD_CONNECT(1L.shl(FD_CONNECT_BIT.value.toInt())),
    FD_CLOSE_BIT(5),
    FD_CLOSE(1L.shl(FD_CLOSE_BIT.value.toInt())),
    FD_QOS_BIT(6),
    FD_QOS(1L.shl(FD_QOS_BIT.value.toInt())),
    FD_GROUP_QOS_BIT(7),
    FD_GROUP_QOS(1L.shl(FD_GROUP_QOS_BIT.value.toInt())),
    FD_ROUTING_INTERFACE_CHANGE_BIT(8),
    FD_ROUTING_INTERFACE_CHANGE(1L.shl(FD_ROUTING_INTERFACE_CHANGE_BIT.value.toInt())),
    FD_ADDRESS_LIST_CHANGE_BIT(9),
    FD_ADDRESS_LIST_CHANGE(1L.shl(FD_ADDRESS_LIST_CHANGE_BIT.value.toInt())),
    FD_MAX_EVENTS(10),
    FD_ALL_EVENTS(1L.shl(FD_MAX_EVENTS.value.toInt()) - 1),
}