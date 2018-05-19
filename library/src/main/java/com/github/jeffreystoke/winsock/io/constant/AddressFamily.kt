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

// 地址类型 AF_XXX
enum class AddressFamily(val value: Int) {
    UNIX(1),
    Internet(2),
    IMPLINK(3),
    PUP(4),
    CHAOS(5),
    NS(6),
    IPX(NS.value),
    ISO(7),
    OSI(ISO.value),
    ECMA(8),
    DATAKIT(9),
    CCITT(10),
    SNA(11),
    DECnet(12),
    DLI(13),
    LAT(14),
    HYLINK(15),
    APPLETALK(16),
    NETBIOS(17),
    VOICEVIEW(18),
    FIREFOX(19),
    UNKNOWN1(20),
    BAN(21),
    ATM(22),
    INET6(23),
    CLUSTER(24),
    IRDA(26),
    MAX(27),
}