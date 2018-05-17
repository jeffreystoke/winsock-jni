package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.struct.CompletionKey
import com.github.jeffreystoke.winsock.io.struct.Socket
import com.github.jeffreystoke.winsock.io.struct.Struct
import com.github.jeffreystoke.winsock.io.struct.WSAOverlapped
import com.github.jeffreystoke.winsock.io.util.isNull

class IOCP(val socket: Socket,
           otherIOCP: IOCP? = null,
           completionKey: CompletionKey,
           numOfThread: Int = Runtime.getRuntime().availableProcessors()) : Struct() {

    init {
        var _other_iocp_ptr = 0L
        if (otherIOCP != null) {
            _other_iocp_ptr = otherIOCP._ptr
        }
        _ptr = WinSock._create_iocp(socket.getPtr(), _other_iocp_ptr, completionKey.getPtr(), numOfThread)

        if (_ptr.isNull()) {
            throw RuntimeException("创建 IOCP 失败")
        }
    }

    fun getQueuedCompletionStatus(bytes: Int, completionKey: CompletionKey, overlapped: WSAOverlapped, waitTimeout: Int): Boolean {
        return WinSock._get_queued_completion_status(_ptr, bytes, completionKey.getPtr(), overlapped.getPtr(), waitTimeout)
    }

    fun postQueuedCompletionStatus(bytes: Int, completionKey: CompletionKey, overlapped: WSAOverlapped): Boolean {
        return WinSock._post_queued_completion_status(_ptr, bytes, completionKey.getPtr(), overlapped.getPtr())
    }

    fun cancel() {
        WinSock._cancel_io(socket.getPtr())
    }
}