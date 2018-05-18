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

import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.struct.CompletionKey
import com.github.jeffreystoke.winsock.io.struct.Socket
import com.github.jeffreystoke.winsock.io.struct.Struct
import com.github.jeffreystoke.winsock.io.struct.WSAOverlapped
import com.github.jeffreystoke.winsock.io.util.isNull

class CompletionPortModel(val socket: Socket,
                          otherCP: CompletionPortModel? = null,
                          completionKey: CompletionKey) : Struct() {

    private var mCallback: Callback? = null

    interface Callback {
        fun onRecv(socket: Socket, data: ByteArray)
        fun onSend(socket: Socket)
        fun onClose(socket: Socket)
        fun onError(socket: Socket)
    }

    companion object {
        private val iocps by lazy { HashMap<Long, CompletionPortModel>() }

        private val _op_read = 0
        private val _op_write = 1
        private val _op_close = 2
        private val _op_error = 3

        fun onMessage(cpPtr: Long, completionKeyPtr: Long, opType: Int, buffer: ByteArray?) {
            val cp = iocps[cpPtr] ?: return

            val cpk = CompletionKey.getCompletionKey(completionKeyPtr) ?: return
            cpk.socket.address = cpk.clientAddress
            cpk.socket.port = cpk.clientPort
            when (opType) {
                _op_read -> cp.mCallback?.onRecv(cpk.socket, buffer!!)
                _op_write -> cp.mCallback?.onSend(cpk.socket)
                _op_close -> cp.mCallback?.onClose(cpk.socket)
                _op_error -> cp.mCallback?.onError(cpk.socket)
            }
        }
    }

    init {
        var _other_cp_ptr = 0L
        if (otherCP != null) {
            _other_cp_ptr = otherCP._ptr
        }
        _ptr = WinSock._create_iocp(socket.getPtr(), _other_cp_ptr, completionKey.getPtr())

        if (_ptr.isNull()) {
            throw RuntimeException("创建 IOCP 失败")
        }
        iocps[_ptr] = this
    }

    @Throws(RuntimeException::class)
    fun createServerThreads(count: Int = Runtime.getRuntime().availableProcessors() * 2) {
        for (i in 0..count) {
            val ret = WinSock._create_server_thread(_ptr)
            if (ret != 0) {
                throw RuntimeException("创建线程 $i 失败, 错误 $ret")
            }
        }
    }

    fun postQueuedCompletionStatus(bytes: Int, completionKey: CompletionKey, overlapped: WSAOverlapped): Boolean {
        return WinSock._post_queued_completion_status(_ptr, bytes, completionKey.getPtr(), overlapped.getPtr())
    }

    fun cancel() {
        WinSock._cancel_io(socket.getPtr())
    }
}