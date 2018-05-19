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

import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.isNull

class FdSet(socketList: List<Socket> = emptyList()) : Struct() {

    init {
        if (socketList.isNotEmpty()) {
            socketList.forEach { s ->
                add(s)
            }
        }
    }

    fun add(socket: Socket) {
        if (_ptr.isNull()) {
            _ptr = WinSock._create_fd_set()
            if (_ptr.isNull()) {
                throw RuntimeException("无法创建 FD_SET")
            }
        }

        WinSock._add_fd(_ptr, socket.getPtr())
    }

    fun remove(socket: Socket) {
        if (_ptr.isNull()) {
            return
        }

        WinSock._remove_fd(_ptr, socket.getPtr())
    }

    fun getSetFd(): Socket? {
        if (_ptr.isNull()) {
            return null
        }

        return Socket.getSocket(WinSock._get_set_fd(_ptr))
    }
}