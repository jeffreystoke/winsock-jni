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

enum class SocketFlag(val value: Int) {
    WSA_FLAG_OVERLAPPED(0x01),
    WSA_FLAG_MULTIPOINT_C_ROOT(0x02),
    WSA_FLAG_MULTIPOINT_C_LEAF(0x04),
    WSA_FLAG_MULTIPOINT_D_ROOT(0x08),
    WSA_FLAG_MULTIPOINT_D_LEAF(0x10),
    WSA_FLAG_ACCESS_SYSTEM_SECURITY(0x40),
    WSA_FLAG_NO_HANDLE_INHERIT(0x80),
    WSA_FLAG_REGISTERED_IO(0x100),
}