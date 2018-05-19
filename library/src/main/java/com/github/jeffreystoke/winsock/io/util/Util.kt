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

package com.github.jeffreystoke.winsock.io.util

import com.github.jeffreystoke.winsock.io.constant.NetEvent
import com.github.jeffreystoke.winsock.io.internal.WinSock

typealias Pointer = Long

fun Pointer.isNull(): Boolean {
    return this < 1
}

fun Array<out NetEvent>.mergedEvent(): Long {
    var event = 0L
    this.forEach { e ->
        event = event.or(e.value)
    }
    return event
}

fun wsaCleanup() = WinSock._wsa_cleanup()

fun wsaGetLastError() = WinSock._wsa_get_last_error()