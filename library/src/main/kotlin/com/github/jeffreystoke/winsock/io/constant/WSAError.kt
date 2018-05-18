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

enum class WSAError(val value: Int) {
    WSA_BASE_ERR(10000),
    WSAEINTR(WSA_BASE_ERR.value + 4),
    WSAEBADF(WSA_BASE_ERR.value + 9),
    WSAEACCES(WSA_BASE_ERR.value + 13),
    WSAEFAULT(WSA_BASE_ERR.value + 14),
    WSAEINVAL(WSA_BASE_ERR.value + 22),
    WSAEMFILE(WSA_BASE_ERR.value + 24),
    WSAEWOULDBLOCK(WSA_BASE_ERR.value + 35),
    WSAEINPROGRESS(WSA_BASE_ERR.value + 36),
    WSAEALREADY(WSA_BASE_ERR.value + 37),
    WSAENOTSOCK(WSA_BASE_ERR.value + 38),
    WSAEDESTADDRREQ(WSA_BASE_ERR.value + 39),
    WSAEMSGSIZE(WSA_BASE_ERR.value + 40),
    WSAEPROTOTYPE(WSA_BASE_ERR.value + 41),
    WSAENOPROTOOPT(WSA_BASE_ERR.value + 42),
    WSAEPROTONOSUPPORT(WSA_BASE_ERR.value + 43),
    WSAESOCKTNOSUPPORT(WSA_BASE_ERR.value + 44),
    WSAEOPNOTSUPP(WSA_BASE_ERR.value + 45),
    WSAEPFNOSUPPORT(WSA_BASE_ERR.value + 46),
    WSAEAFNOSUPPORT(WSA_BASE_ERR.value + 47),
    WSAEADDRINUSE(WSA_BASE_ERR.value + 48),
    WSAEADDRNOTAVAIL(WSA_BASE_ERR.value + 49),
    WSAENETDOWN(WSA_BASE_ERR.value + 50),
    WSAENETUNREACH(WSA_BASE_ERR.value + 51),
    WSAENETRESET(WSA_BASE_ERR.value + 52),
    WSAECONNABORTED(WSA_BASE_ERR.value + 53),
    WSAECONNRESET(WSA_BASE_ERR.value + 54),
    WSAENOBUFS(WSA_BASE_ERR.value + 55),
    WSAEISCONN(WSA_BASE_ERR.value + 56),
    WSAENOTCONN(WSA_BASE_ERR.value + 57),
    WSAESHUTDOWN(WSA_BASE_ERR.value + 58),
    WSAETOOMANYREFS(WSA_BASE_ERR.value + 59),
    WSAETIMEDOUT(WSA_BASE_ERR.value + 60),
    WSAECONNREFUSED(WSA_BASE_ERR.value + 61),
    WSAELOOP(WSA_BASE_ERR.value + 62),
    WSAENAMETOOLONG(WSA_BASE_ERR.value + 63),
    WSAEHOSTDOWN(WSA_BASE_ERR.value + 64),
    WSAEHOSTUNREACH(WSA_BASE_ERR.value + 65),
    WSAENOTEMPTY(WSA_BASE_ERR.value + 66),
    WSAEPROCLIM(WSA_BASE_ERR.value + 67),
    WSAEUSERS(WSA_BASE_ERR.value + 68),
    WSAEDQUOT(WSA_BASE_ERR.value + 69),
    WSAESTALE(WSA_BASE_ERR.value + 70),
    WSAEREMOTE(WSA_BASE_ERR.value + 71),
    WSASYSNOTREADY(WSA_BASE_ERR.value + 91),
    WSAVERNOTSUPPORTED(WSA_BASE_ERR.value + 92),
    WSANOTINITIALISED(WSA_BASE_ERR.value + 93),
    WSAEDISCON(WSA_BASE_ERR.value + 101),
    WSAENOMORE(WSA_BASE_ERR.value + 102),
    WSAECANCELLED(WSA_BASE_ERR.value + 103),
    WSAEINVALIDPROCTABLE(WSA_BASE_ERR.value + 104),
    WSAEINVALIDPROVIDER(WSA_BASE_ERR.value + 105),
    WSAEPROVIDERFAILEDINIT(WSA_BASE_ERR.value + 106),
    WSASYSCALLFAILURE(WSA_BASE_ERR.value + 107),
    WSASERVICE_NOT_FOUND(WSA_BASE_ERR.value + 108),
    WSATYPE_NOT_FOUND(WSA_BASE_ERR.value + 109),
    WSA_E_NO_MORE(WSA_BASE_ERR.value + 110),
    WSA_E_CANCELLED(WSA_BASE_ERR.value + 111),
    WSAEREFUSED(WSA_BASE_ERR.value + 112),
    WSAHOST_NOT_FOUND(WSA_BASE_ERR.value + 1001),
    WSATRY_AGAIN(WSA_BASE_ERR.value + 1002),
    WSANO_RECOVERY(WSA_BASE_ERR.value + 1003),
    WSANO_DATA(WSA_BASE_ERR.value + 1004),
    WSA_QOS_RECEIVERS(WSA_BASE_ERR.value + 1005),
    WSA_QOS_SENDERS(WSA_BASE_ERR.value + 1006),
    WSA_QOS_NO_SENDERS(WSA_BASE_ERR.value + 1007),
    WSA_QOS_NO_RECEIVERS(WSA_BASE_ERR.value + 1008),
    WSA_QOS_REQUEST_CONFIRMED(WSA_BASE_ERR.value + 1009),
    WSA_QOS_ADMISSION_FAILURE(WSA_BASE_ERR.value + 1010),
    WSA_QOS_POLICY_FAILURE(WSA_BASE_ERR.value + 1011),
    WSA_QOS_BAD_STYLE(WSA_BASE_ERR.value + 1012),
    WSA_QOS_BAD_OBJECT(WSA_BASE_ERR.value + 1013),
    WSA_QOS_TRAFFIC_CTRL_ERROR(WSA_BASE_ERR.value + 1014),
    WSA_QOS_GENERIC_ERROR(WSA_BASE_ERR.value + 1015)
}