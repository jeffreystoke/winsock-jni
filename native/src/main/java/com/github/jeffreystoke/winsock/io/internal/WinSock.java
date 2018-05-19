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

package com.github.jeffreystoke.winsock.io.internal;

import java.io.IOException;

// JNI Bindings
public class WinSock {

    public static final int WSA_WAIT_EVENT_0;

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
        WSA_WAIT_EVENT_0 = _get_wsa_wait_event_0();
    }

    private static native String _wsa_startup();

    private static native int _get_wsa_wait_event_0();

    // delete
    public static native void _free(long ptr);

    // WSACleanup()
    public static native void _wsa_cleanup();

    // WSAGetLastError()
    public static native int _wsa_get_last_error();

    // setsockopt()
    public static native int _setsockopt(long s, int level, int optKey, byte[] optVal);

    // getsockopt()
    public static native int _getsockopt(long s, int level, int optKey, byte[] optVal);

    // TODO
    // ioctlsocket()
    public static native long _ioctlsocket(long s, boolean nonBlock);

    // socket()
    public static native long _socket(int addressFamily, int socketType, int proto);

    // bind()
    public static native long _bind(long s, String address, int port);

    // listen()
    public static native int _listen(long s, int backlog);

    // accpet()
    public static native long _accept(long s, byte[] addressBuf, byte[] portBuf);

    // recv()
    public static native int _recv(long s, byte[] buf, int flag);

    // send()
    public static native int _send(long s, byte[] buf, int flag);

    // closesocket()
    public static native int _closesocket(long s);

    // shutdown()
    public static native int _shutdown(long s, int how);

    // connect()
    public static native int _connect(long s, String address, int port);

    // recvfrom()
    public static native int _recv_from(long s, byte[] buf, int flag, byte[] addressBuf, byte[] portBuf);

    // sendto()
    public static native int _send_to(long s, byte[] buf, int flag, String remoteAddress, int port);

    // select()
    public static native long _select(long[] readFDs, long[] writeFDs, long[] exceptionFDs, int timeout, byte[] bufForLong);

    // WSACreateEvent()
    public static native long _wsa_create_event();

    // WSAResetEvent()
    public static native boolean _wsa_reset_event(long event);

    // WSACloseEvent()
    public static native boolean _wsa_close_event(long event);

    // WSAWaitForMultipleEvents()
    public static native int _wsa_wait_for_multiple_events(int count, long[] events, boolean waitAll, int waitTimeout, boolean alert_able);

    // WSAEventSelect()
    public static native int _wsa_event_select(long s, long event, long netEvents);

    // WSAEnumNetworkEvents()
    public static native int _wsa_enum_network_events(long s, long event, byte[] bufForLong, byte[] bufForInt);

    // WSAScoket()
    public static native long _wsa_socket(int addressFamily, int socketType, int proto, int flag);

    // WSARecv()
    public static native int _wsa_recv(long s, int bufSize, long overlappedStruct);

    // WSASend()
    public static native int _wsa_send(long s, byte[] data, long overlappedStruct);

    public static native long _create_completion_key(long socket, String remoteAddress, int port);

    public static native void _destroy_completion_key(long keyPtr);

    public static native long _create_wsa_overlapped(long wsaEvent);

    public static native int _wsa_get_overlapped_result(long s, long wsaOverlapped, boolean wait, long flag);

    public static native long _create_iocp(long socket, long existingCP, long completionKey);

    public static native int _create_server_thread(long cp);

    public static native boolean _cancel_io(long fileHandle);

    public static native boolean _post_queued_completion_status(long cpHandler, int bytesToTrans, long completionKey, long overlapped);
}
