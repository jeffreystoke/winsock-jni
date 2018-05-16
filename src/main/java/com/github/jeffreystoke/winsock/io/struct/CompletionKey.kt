package com.github.jeffreystoke.winsock.io.struct

import com.github.jeffreystoke.winsock.io.internal.WinSock._create_completion_key
import com.github.jeffreystoke.winsock.io.util.isNull

class CompletionKey(socket: Socket, clientAddress: String) : Struct() {

    init {
        _ptr = _create_completion_key(socket.getPtr(), clientAddress)
        if (_ptr.isNull()) {
            throw RuntimeException("创建 CompletionKey 失败")
        }
    }
}