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

import com.github.jeffreystoke.winsock.io.struct.Socket
import org.junit.jupiter.api.Test

class SocketTest {

    private val sListenAddress = "127.0.0.1"
    private val sListenPort = 4567

    private val mServerSocket = Socket()
    private var mSocket = Socket()

    @Test
    fun connectTest() {
        mServerSocket.bind(sListenAddress, sListenPort)
        mServerSocket.listen(0)
    }

    @Test
    fun sendTest() {
    }

    @Test
    fun recvTest() {
    }

    @Test
    fun acceptTest() {
    }

    @Test
    fun shutdownTest() {
    }

    @Test
    fun closeTest() {
    }

    @Test
    fun getOptionTest() {
    }

    @Test
    fun setOptionTest() {
    }
}