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

enum class SocketOption(val value: Int) {
    SO_DEBUG(0x0001),
    SO_ACCEPTCONN(0x0002),
    SO_REUSEADDR(0x0004),
    SO_KEEPALIVE(0x0008),
    SO_DONTROUTE(0x0010),
    SO_BROADCAST(0x0020),
    SO_USELOOPBACK(0x0040),
    SO_LINGER(0x0080),
    SO_OOBINLINE(0x0100),
    SO_SNDBUF(0x1001),
    SO_RCVBUF(0x1002),
    SO_SNDLOWAT(0x1003),
    SO_RCVLOWAT(0x1004),
    SO_SNDTIMEO(0x1005),
    SO_RCVTIMEO(0x1006),
    SO_ERROR(0x1007),
    SO_TYPE(0x1008),
    SO_GROUP_ID(0x2001),
    SO_GROUP_PRIORITY(0x2002),
    SO_MAX_MSG_SIZE(0x2003),
    SO_PROTOCOL_INFOA(0x2004),
    SO_PROTOCOL_INFOW(0x2005),
    SO_DONTLINGER(SO_LINGER.value),
    SO_EXCLUSIVEADDRUSE(SO_REUSEADDR.value.inv())
}