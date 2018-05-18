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