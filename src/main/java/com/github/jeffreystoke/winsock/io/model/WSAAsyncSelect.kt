package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.constant.NetEvent
import com.github.jeffreystoke.winsock.io.internal.Pointer
import com.github.jeffreystoke.winsock.io.internal.WinSock
import com.github.jeffreystoke.winsock.io.struct.Socket
import com.github.jeffreystoke.winsock.io.util.isNull
import com.github.jeffreystoke.winsock.io.util.mergedResult

object WSAAsyncSelect {

    private val NET_MESSAGE = 1021

    private var mCallback: Callback? = null

    private fun _onMessage(wParam: Pointer, lParam: Pointer) {
        if (WinSock._wsaGetSelectError(lParam) != 0L) {
            mCallback?.onError(Socket(wParam))
            return
        }

        val socket = Socket(wParam)
        when (lParam) {
            NetEvent.FD_ACCEPT.value -> mCallback?.onAccept(socket)
            NetEvent.FD_READ.value -> mCallback?.onRead(socket)
            NetEvent.FD_WRITE.value -> mCallback?.onWrite(socket)
            NetEvent.FD_CLOSE.value -> mCallback?.onClose(socket)
        }

        mCallback?.onOtherMessage(Socket(wParam), WinSock._wsaGetSelectEvent(lParam))
    }

    private val _window_ptr: Pointer by lazy {
        val ptr = WinSock._createWindow()
        if (ptr.isNull()) {
            throw RuntimeException("无法创建窗口")
        }
        return@lazy ptr
    }

    fun start(socket: Socket, caredNetEvents: Array<NetEvent>): Int =
            WinSock._wsaAsyncSelect(socket.getPtr(), _window_ptr, NET_MESSAGE, caredNetEvents.mergedResult())

    interface Callback {
        fun onError(socket: Socket)

        fun onRead(socket: Socket)
        fun onWrite(socket: Socket)
        fun onAccept(socket: Socket)
        fun onClose(socket: Socket)

        fun onOtherMessage(socket: Socket, netEvent: Long)
    }
}