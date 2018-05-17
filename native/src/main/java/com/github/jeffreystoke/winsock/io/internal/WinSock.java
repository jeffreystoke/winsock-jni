package com.github.jeffreystoke.winsock.io.internal;

import java.io.IOException;

// JNI Bindings
public class WinSock {

    public static native String _wsa_startup();

    static {
        try {
            System.loadLibrary("winsock_jni");
        } catch (UnsatisfiedLinkError e) {
            String platform = "windows_";
            String arch = System.getProperty("os.arch");
            if ("x86".equalsIgnoreCase(arch) || "i386".equalsIgnoreCase(arch) ||
                    "i486".equalsIgnoreCase(arch) || "i586".equalsIgnoreCase(arch) ||
                    "i686".equalsIgnoreCase(arch)) {
                platform += "i386";
            } else if ("x86_64".equalsIgnoreCase(arch) || "amd64".equalsIgnoreCase(arch)) {
                platform += "amd64";
            } else {
                throw new UnsupportedOperationException("unsupported arch");
            }

            try {
                NativeUtils.loadLibraryFromJar("/natives/" + platform + "/winsock_jni.dll");
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }

        String err = _wsa_startup();
        if (err != null) {
            throw new RuntimeException(err);
        }
    }

    // free in <cstdlib>
    public static native void _free(long ptr);

    // WSACleanup() 结束 WinSock 的使用, 调用将清空所有 Socket
    public static native void _wsa_cleanup();

    // WSAGetLastError()
    public static native int _wsa_get_last_error();

    // setsockopt()
    public static native int _setsockopt(long s, int level, int optKey, byte[] optVal);

    // getsockopt()
    public static native int _getsockopt(long s, int level, int optKey, byte[] optVal);

    // TODO
    // ioctlsocket() 主要用于设置 Socket 阻塞/非阻塞模式
    public static native long _ioctlsocket(long s, boolean nonBlock);

    // socket() 创建 Windows 平台原生 Socket
    public static native long _socket(int addressFamily, int socketType, int proto);

    // bind() 将 Socket 与地址绑定, 仅支持 IPv4
    public static native long _bind(long s, String address, int port);

    // listen() 监听 Socket
    public static native int _listen(long s, int backlog);

    // accpet() 接受连接
    public static native long _accept(long s, byte[] addressBuf, byte[] portBuf);

    // recv() 接收数据
    public static native int _recv(long s, byte[] buf, int flag);

    // send() 发送数据
    public static native int _send(long s, byte[] buf, int flag);

    // closesocket() 关闭 Socket 连接
    public static native int _closesocket(long s);

    // shutdown() 关闭 Socket 通道 (读, 写, 全部)
    public static native int _shutdown(long s, int how);

    // connect() 连接服务端, 仅支持 IPv4
    public static native int _connect(long s, String address, int port);

    // recvfrom() UDP 接收数据
    public static native int _recv_from(long s, byte[] buf, int flag, byte[] addressBuf, byte[] portBuf);

    // sendto() UDP 发送数据
    public static native int _send_to(long s, byte[] buf, int flag, String remoteAddress, int port);

    public static native long _create_fd_set();

    public static native void _add_fd(long fdSet, long s);

    public static native void _remove_fd(long fdSet, long s);

    public static native long _get_set_fd(long fdSet);

    // select()
    public static native int _select(long readFDs, long writeFDs, long exceptionFDs, int timeout);

    // WSACreateEvent() 创建 WSAEvent
    public static native long _wsa_create_event();

    // WSAResetEvent() 将 WSAEvent 设置为未传信
    public static native boolean _wsa_reset_event(long event);

    // WSACloseEvent() 关闭 WSAEvent
    public static native boolean _wsa_close_event(long event);

    // WSAWaitForMultipleEvents()
    public static native int _wsa_wait_for_multiple_events(int count, long[] events, boolean waitAll, int waitTimeout, boolean alert_able);

    // WSAEventSelect()
    public static native int _wsa_event_select(long s, long event, long netEvents);

    // WSAEnumNetworkEvents()
    public static native int _wsa_enum_network_events(long s, long event, byte[] bufForLong, byte[] bufForInt);

    // WSAScoket() 创建适用于 Overlapped I/O 以及 ICOP 的 Socket
    public static native long _wsa_socket(int addressFamily, int socketType, int proto, int flag);

    // WSARecv() Overlapped I/O 以及 IOCP 接收数据
    public static native int _wsa_recv(long s, long[] buffers, int bytesToRead, int flag, long overlappedStruct);

    // WSASend() Overlapped I/O 以及 IOCP 发送数据
    public static native int _wsa_send(long s, long[] buffers, int bytesToSend, int flag, long overlappedStruct);

    public static native long _create_wsa_buf(int size);

    public static native void _destroy_wsa_buf(long wsaBuf);

    public static native long _create_completion_key(long socket, String remoteAddress, int port);

    public static native long _create_wsa_overlapped(int internal, int internalHigh, int offset, int offsetHigh, long wsaEvent);

    public static native boolean _wsa_get_overlapped_result(long s, long wsaOverlapped, int bytesToTrans, boolean wait, long flag);

    public static native long _create_iocp(long fileHandle, long existingCP, long completionKey, int numOfCurrentThreads);

    public static native boolean _get_queued_completion_status(long cpHandler, int bytesToTrans, long completionKey, long overlapped, int waitTimeout);

    public static native boolean _cancel_io(long fileHandle);

    public static native boolean _post_queued_completion_status(long cpHandler, int bytesToTrans, long completionKey, long overlapped);
}
