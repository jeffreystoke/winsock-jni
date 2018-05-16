@file:Suppress("FunctionName")

package com.github.jeffreystoke.winsock.io.internal

typealias Pointer = Long

object WinSock {

    init {
        System.loadLibrary("winsock_jni")
        _wsa_startup()?.let { err -> throw RuntimeException(err) }
    }

    @JvmStatic
    external fun _free(ptr: Pointer)

    @JvmStatic
    private external fun _wsa_startup(): String?

    @JvmStatic
    external fun _wsa_cleanup()

    @JvmStatic
    external fun _wsa_get_last_error(): Int

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
    external fun _create_fd_set(): Pointer

    @JvmStatic
    external fun _add_fd(fdSet: Pointer, s: Pointer)

    @JvmStatic
    external fun _remove_fd(fdSet: Pointer, s: Pointer)

    @JvmStatic
    external fun _get_set_fd(fdSet: Pointer): Pointer

    @JvmStatic
    external fun _select(readFDs: Pointer, writeFDs: Pointer, exceptionFDs: Pointer, timeout: Int): Int

    // 事件通知
    @JvmStatic
    external fun _wsa_create_event(): Pointer

    @JvmStatic
    external fun _wsa_reset_event(event: Pointer): Boolean

    @JvmStatic
    external fun _wsa_close_event(event: Pointer): Boolean

    @JvmStatic
    external fun _wsa_wait_for_multiple_events(count: Int, events: Array<Pointer>, waitAll: Boolean, waitTimeout: Int, alert_able: Boolean): Int

    @JvmStatic
    external fun _wsa_event_select(s: Pointer, event: Pointer, netEvents: Long): Int

    @JvmStatic
    external fun _wsa_enum_network_events(s: Pointer, event: Pointer, bufForLong: ByteArray, bufForInt: ByteArray): Int

    @JvmStatic
    external fun _wsa_connect()

    @JvmStatic
    external fun _wsa_accept(s: Pointer): Pointer

    // 重叠 I/O
    @JvmStatic
    external fun _wsa_socket(addressFamily: Int, socketType: Int, proto: Int, flag: Int): Pointer

    @JvmStatic
    external fun _wsa_recv(s: Pointer, buf: Array<ByteArray>, toRead: Int, flag: Int, overlappedStruct: Pointer)

    @JvmStatic
    external fun _wsa_recv_from()

    @JvmStatic
    external fun _wsa_send()

    @JvmStatic
    external fun _wsa_send_to()

    @JvmStatic
    external fun _create_completion_key(socket: Pointer, clientAddress: String): Pointer

    @JvmStatic
    private external fun _create_wsa_overlapped(internal: Int, internalHigh: Int, offset: Int, offsetHigh: Int, wsaEvent: Pointer): Pointer

    @JvmStatic
    external fun _wsa_get_overlapped_result(s: Pointer, wsaOverlapped: Pointer, wait: Boolean, flag: Pointer): Boolean

    // IOCP
    @JvmStatic
    external fun _create_iocp(fileHandle: Pointer, existingCP: Pointer, completionKey: Pointer, numOfCurrentThreads: Int): Pointer

    @JvmStatic
    external fun _get_queued_completion_status(cpHandler: Pointer, bytesRead: Int, completionKey: Pointer, overlapped: Pointer, waitTimeout: Int): Boolean

    @JvmStatic
    external fun _cancel_io(fileHandle: Pointer)

    @JvmStatic
    external fun _post_queued_completion_status(cpHandler: Pointer, bytesTx: Int, completionKey: Pointer, overlapped: Pointer): Boolean
}
