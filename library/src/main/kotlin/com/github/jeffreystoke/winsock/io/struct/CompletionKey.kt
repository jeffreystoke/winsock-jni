package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.util.isNull

class CompletionKey(val socket: Socket, val clientAddress: String, val clientPort: Int) : Struct() {

    init {
        _ptr = WinSock._create_completion_key(socket.getPtr(), clientAddress, clientPort)
        if (_ptr.isNull()) {
            throw RuntimeException("创建 CompletionKey 失败")
        }
    }
}