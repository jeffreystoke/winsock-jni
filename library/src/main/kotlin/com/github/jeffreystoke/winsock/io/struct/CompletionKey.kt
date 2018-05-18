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

class CompletionKey(val socket: Socket,
                    val clientAddress: String = socket.address,
                    val clientPort: Int = socket.port) : Struct() {

    companion object {
        private val keys by lazy { HashMap<Long, CompletionKey>() }

        fun getCompletionKey(ptr: Long): CompletionKey? {
            return keys[ptr]
        }
    }

    init {
        _ptr = WinSock._create_completion_key(socket.getPtr(), clientAddress, clientPort)
        if (_ptr.isNull()) {
            throw RuntimeException("创建 CompletionKey 失败")
        }
        keys[_ptr] = this
    }

    override fun destroy() {
        WinSock._destroy_completion_key(_ptr)
    }
}