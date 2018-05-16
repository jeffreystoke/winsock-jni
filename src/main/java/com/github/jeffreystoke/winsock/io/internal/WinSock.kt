package com.github.jeffreystoke.winsock.io.internal

typealias Pointer = Long

object WinSock {

    init {
        System.loadLibrary("winsock_jni")
        _wsaStartup()?.let { err -> throw RuntimeException(err) }
    }

    @JvmStatic
    external fun _free(ptr: Pointer)

    @JvmStatic
    private external fun _wsaStartup(): String?

    @JvmStatic
    external fun _wsaCleanup()

    @JvmStatic
    external fun _wsaGetLastError(): Int

    @JvmStatic
    external fun _setsockopt(s: Pointer, level: Int, optKey: Int, optVal: ByteArray): Int

    @JvmStatic
    external fun _getsockopt(s: Pointer, level: Int, optKey: Int, optVal: ByteArray): Int

    @JvmStatic
    external fun _ioctlsocket(s: Pointer, mode: Int)

    @JvmStatic
    external fun _socket(addressFamily: Int, socketType: Int, proto: Int): Pointer

    @JvmStatic
    external fun _bind(s: Pointer, address: String, port: Int)

    @JvmStatic
    external fun _listen(s: Pointer, backlog: Int): Int

    // TODO 远端地址记录
    @JvmStatic
    external fun _accept(s: Pointer): Pointer

    @JvmStatic
    external fun _recv(s: Pointer, buf: ByteArray, flag: Int): Int

    @JvmStatic
    external fun _send(s: Pointer, buf: ByteArray, flag: Int): Int

    @JvmStatic
    external fun _closesocket(s: Pointer): Int

    @JvmStatic
    external fun _shutdown(s: Pointer, how: Int): Int

    @JvmStatic
    external fun _connect(s: Pointer, address: String, port: Int): Int

    // UDP
    // TODO 远端地址记录
    @JvmStatic
    external fun _recvFrom(s: Pointer, buf: ByteArray, flag: Int): Int

    @JvmStatic
    external fun _sendTo(s: Pointer, buf: ByteArray, flag: Int, remoteAddress: String): Int

    @JvmStatic
    external fun _createFdSet(): Pointer

    @JvmStatic
    external fun _addFd(fdSet: Pointer, s: Pointer)

    @JvmStatic
    external fun _removeFd(fdSet: Pointer, s: Pointer)

    @JvmStatic
    external fun _getSetFd(fdSet: Pointer): Pointer

    @JvmStatic
    external fun _select(readFDs: Pointer, writeFDs: Pointer, exceptionFDs: Pointer, timeout: Int): Int

    // 事件通知
    @JvmStatic
    external fun _wsaCreateEvent(): Pointer

    @JvmStatic
    external fun _wsaResetEvent(event: Pointer): Boolean

    @JvmStatic
    external fun _wsaCloseEvent(event: Pointer): Boolean

    @JvmStatic
    external fun _wsaWaitForMultipleEvents(count: Int, events: Array<Pointer>, waitAll: Boolean, waitTimeout: Int, alert_able: Boolean): Int

    @JvmStatic
    external fun _wsaEventSelect(s: Pointer, event: Pointer, netEvents: Long): Int

    // TODO 检查错误并回调
    @JvmStatic
    external fun _wsaEnumNetworkEvents(s: Pointer, event: Pointer, bufForLong: ByteArray): Int

    @JvmStatic
    external fun _wsa_connect()

    @JvmStatic
    external fun _wsa_accept(s: Pointer): Pointer

    // 重叠 I/O
    @JvmStatic
    external fun _wsaSocket(addressFamily: Int, socketType: Int, proto: Int, flag: Int): Pointer

    @JvmStatic
    external fun _wsaRecv(s: Pointer, buf: Array<ByteArray>, toRead: Int, flag: Int, overlappedStruct: Pointer)

    @JvmStatic
    external fun _wsaRecvFrom()

    @JvmStatic
    external fun _wsaSend()

    @JvmStatic
    external fun _wsaSendTo()

    @JvmStatic
    external fun _create_CompletionKey(socket: Pointer, clientAddress: String): Pointer

    @JvmStatic
    private external fun _createWSAOverlapped(internal: Int, internalHigh: Int, offset: Int, offsetHigh: Int, wsaEvent: Pointer): Pointer

    @JvmStatic
    external fun _wsaGetOverlappedResult(s: Pointer, wsaOverlapped: Pointer, wait: Boolean, flag: Pointer): Boolean

    // IOCP
    @JvmStatic
    external fun _createIOCP(fileHandle: Pointer, existingCP: Pointer, completionKey: Pointer, numOfCurrentThreads: Int): Pointer

    @JvmStatic
    external fun _getQueuedCompletionStatus(cpHandler: Pointer, bytesRead: Int, completionKey: Pointer, overlapped: Pointer, waitTimeout: Int): Boolean

    @JvmStatic
    external fun _cancelIO(fileHandle: Pointer)

    @JvmStatic
    external fun _postQueuedCompletionStatus(cpHandler: Pointer, bytesTx: Int, completionKey: Pointer, overlapped: Pointer): Boolean
}
