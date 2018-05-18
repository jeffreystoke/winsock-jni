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

import com.github.jeffreystoke.winsock.io.constant.AddressFamily
import com.github.jeffreystoke.winsock.io.constant.ProtocolType
import com.github.jeffreystoke.winsock.io.constant.SocketFlag
import com.github.jeffreystoke.winsock.io.constant.SocketType
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.isNull
import java.io.IOException

class WSASocket(addressFamily: AddressFamily = AddressFamily.Internet,
                type: SocketType = SocketType.Stream,
                protocol: ProtocolType = ProtocolType.TCP,
                flag: SocketFlag = SocketFlag.WSA_FLAG_OVERLAPPED) : Socket() {

    init {
        _ptr = WinSock._wsa_socket(addressFamily.value, type.value, protocol.value, flag.value)
        if (_ptr.isNull()) {
            throw RuntimeException("无发创建 WSASocket")
        }
    }

    @Throws(IOException::class)
    fun wsaRecv(buf: ByteArray, overlapped: WSAOverlapped): Int {
        return WinSock._wsa_recv(_ptr, buf, overlapped.getPtr())
    }

    @Throws(IOException::class)
    fun wsaSend(data: ByteArray, overlapped: WSAOverlapped): Int {
        return WinSock._wsa_send(_ptr, data, overlapped.getPtr())
    }
}