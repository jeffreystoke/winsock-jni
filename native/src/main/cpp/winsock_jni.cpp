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

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <cstdio>
#include <cstdlib>

#include <jni.h>

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Mswsock.h>
#include <windows.h>

// link against winsock2.lib
#pragma comment(lib, "WS2_32")

#ifndef _Included_com_github_jeffreystoke_winsock_io_internal_WinSock
#define _Included_com_github_jeffreystoke_winsock_io_internal_WinSock
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1free(
    JNIEnv *env, jclass clazz, jlong ptr)
{
    delete reinterpret_cast<void *>(ptr);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _get_wsa_wait_event_0
 * Signature: ()I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1get_1wsa_1wait_1event_10(
    JNIEnv *env, jclass clazz)
{
    return WSA_WAIT_EVENT_0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_startup
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1startup(
    JNIEnv *env, jclass clazz)
{
    WSADATA wsaData;
    WORD sockVersion = MAKEWORD(2, 2);

    if (WSAStartup(sockVersion, &wsaData) != 0)
    {
        return env->NewStringUTF("ERROR init winsock lib");
    }

    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_cleanup
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1cleanup(
    JNIEnv *env, jclass)
{
    WSACleanup();
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_get_last_error
 * Signature: ()I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1get_1last_1error(
    JNIEnv *env, jclass)
{
    return WSAGetLastError();
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _setsockopt
 * Signature: (JII[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1setsockopt(
    JNIEnv *env, jclass clazz, jlong socket, jint level, jint optKey, jbyteArray optVal)
{
    auto len = env->GetArrayLength(optVal);
    auto buf = new char[len];
    env->GetByteArrayRegion(optVal, 0, len, reinterpret_cast<jbyte *>(buf));
    int ret = setsockopt(static_cast<SOCKET>(socket), level, optKey, buf, len);
    delete buf;
    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _getsockopt
 * Signature: (JII[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1getsockopt(
    JNIEnv *env, jclass clazz, jlong socket, jint level, jint optKey, jbyteArray retBuf)
{
    int len = env->GetArrayLength(retBuf);
    auto buf = new char[len];
    auto ret = getsockopt(static_cast<SOCKET>(socket), level, optKey, buf, &len);
    env->SetByteArrayRegion(retBuf, 0, len, reinterpret_cast<jbyte *>(buf));
    delete buf;
    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _ioctlsocket
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1ioctlsocket(
    JNIEnv *env, jclass clazz, jlong socket, jint mode)
{
    // TODO
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _socket
 * Signature: (III)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1socket(
    JNIEnv *env, jclass clazz, jint af, jint sockType, jint proto)
{
    return socket(af, sockType, proto);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _bind
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1bind(
    JNIEnv *env, jclass clazz, jlong socket, jstring address, jint port)
{

    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_port = htons((u_short)port);
    auto addr = env->GetStringUTFChars(address, nullptr);
    sin.sin_addr.s_addr = inet_addr(addr);
    env->ReleaseStringUTFChars(address, addr);

    bind(static_cast<SOCKET>(socket), (LPSOCKADDR)&sin, sizeof(sin));
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _listen
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1listen(
    JNIEnv *env, jclass clazz, jlong socket, jint backlog)
{
    return listen(static_cast<SOCKET>(socket), backlog);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _accept
 * Signature: (J[B[B)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1accept(
    JNIEnv *env, jclass clazz, jlong socket, jbyteArray addressBuf, jbyteArray portBuf)
{

    sockaddr_in sin{};
    int len = sizeof(sockaddr_in);
    SOCKET ret = accept(static_cast<SOCKET>(socket), reinterpret_cast<sockaddr *>(&sin), &len);

    int addressBufLen = env->GetArrayLength(addressBuf);
    char *address_buf = new char[addressBufLen];
    for (int i = 0; i < addressBufLen; ++i)
    {
        address_buf[i] = (sin.sin_addr.s_addr >> (8 * i)) & 0xFF;
    }
    env->SetByteArrayRegion(addressBuf, 0, addressBufLen, reinterpret_cast<jbyte *>(address_buf));
    delete address_buf;

    int portBufLen = env->GetArrayLength(portBuf);
    char *port_buf = new char[portBufLen];
    for (int i = 0; i < portBufLen; ++i)
    {
        port_buf[i] = ((sin.sin_port >> (8 * i)) & 0XFF);
    }
    env->SetByteArrayRegion(portBuf, 0, portBufLen, reinterpret_cast<jbyte *>(port_buf));
    delete port_buf;

    return (jlong)ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _recv
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1recv(
    JNIEnv *env, jclass clazz, jlong socket, jbyteArray recvBuf, jint flag)
{
    int len = env->GetArrayLength(recvBuf);
    auto buf = new char[len];
    int ret = recv(static_cast<SOCKET>(socket), buf, len, flag);
    env->SetByteArrayRegion(recvBuf, 0, len, reinterpret_cast<jbyte *>(buf));
    delete buf;
    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _send
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1send(
    JNIEnv *env, jclass clazz, jlong socket, jbyteArray sendBuf, jint flag)
{
    int len = env->GetArrayLength(sendBuf);
    auto buf = new char[len];
    env->GetByteArrayRegion(sendBuf, 0, len, reinterpret_cast<jbyte *>(buf));
    int ret = send(static_cast<SOCKET>(socket), buf, len, flag);
    delete buf;
    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _closesocket
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1closesocket(
    JNIEnv *env, jclass clazz, jlong socket)
{
    return closesocket(static_cast<SOCKET>(socket));
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _shutdown
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1shutdown(
    JNIEnv *env, jclass clazz, jlong socket, jint method)
{
    return shutdown(static_cast<SOCKET>(socket), method);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _connect
 * Signature: (JLjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1connect(
    JNIEnv *env, jclass clazz, jlong socket, jstring rAddress, jint port)
{

    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_port = htons((u_short)port);
    auto addr = env->GetStringUTFChars(rAddress, nullptr);
    sin.sin_addr.s_addr = inet_addr(addr);
    env->ReleaseStringUTFChars(rAddress, addr);

    return connect(static_cast<SOCKET>(socket), reinterpret_cast<const sockaddr *>(&sin), sizeof(sin));
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _recv_from
 * Signature: (J[BI[B[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1recv_1from(
    JNIEnv *env, jclass clazz, jlong socket, jbyteArray recvBuf, jint flag, jbyteArray addressBuf, jbyteArray portBuf)
{
    sockaddr_in sin{};
    int addr_len = sizeof(sin);
    int len = env->GetArrayLength(recvBuf);
    auto buf = new char[len];
    int ret = recvfrom(static_cast<SOCKET>(socket), buf, len, flag, (SOCKADDR *)&sin, &addr_len);
    env->SetByteArrayRegion(recvBuf, 0, len, reinterpret_cast<jbyte *>(buf));
    delete buf;

    int addressBufLen = env->GetArrayLength(recvBuf);
    char *address_buf = new char[addressBufLen];
    for (int i = 0; i < addressBufLen; ++i)
    {
        address_buf[i] = (sin.sin_addr.s_addr >> (8 * i)) & 0xFF;
    }
    env->SetByteArrayRegion(addressBuf, 0, addressBufLen, reinterpret_cast<jbyte *>(address_buf));
    delete address_buf;

    int portBufLen = env->GetArrayLength(portBuf);
    char *port_buf = new char[portBufLen];
    for (int i = 0; i < portBufLen; ++i)
    {
        port_buf[i] = ((sin.sin_port >> (8 * i)) & 0XFF);
    }
    env->SetByteArrayRegion(portBuf, 0, portBufLen, reinterpret_cast<jbyte *>(port_buf));
    delete port_buf;

    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _send_to
 * Signature: (J[BILjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1send_1to(
    JNIEnv *env, jclass clazz, jlong socket, jbyteArray buf, jint flag, jstring rAddress, jint port)
{
    int len = env->GetArrayLength(buf);
    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_port = htons((u_short)port);
    auto addr = env->GetStringUTFChars(rAddress, nullptr);
    sin.sin_addr.s_addr = inet_addr(addr);
    env->ReleaseStringUTFChars(rAddress, addr);

    char *c_buf = new char[len];
    int ret = sendto(static_cast<SOCKET>(socket), c_buf, len, flag, (SOCKADDR *)&sin, sizeof(sin));
    env->SetByteArrayRegion(buf, 0, len, reinterpret_cast<jbyte *>(c_buf));
    delete c_buf;

    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_fd_set
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1fd_1set(
    JNIEnv *env, jclass clazz)
{
    fd_set *fdSet = new fd_set{};
    FD_ZERO(fdSet);
    return (jlong)fdSet;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _add_fd
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1add_1fd(
    JNIEnv *env, jclass clazz, jlong fdset, jlong socket)
{
    FD_SET((SOCKET)socket, (fd_set *)fdset);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _remove_fd
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1remove_1fd(
    JNIEnv *env, jclass clazz, jlong fdset, jlong socket)
{
    FD_CLR(static_cast<SOCKET>(socket), (fd_set *)fdset);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _getSetFd
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1get_1set_1fd(
    JNIEnv *env, jclass clazz, jlong fdset)
{
    auto fdSocket = ((fd_set *)fdset);

    for (int i = 0; i < (int)fdSocket->fd_count; i++)
    {
        if (FD_ISSET(fdSocket->fd_array[i], fdSocket))
        {
            return (jlong)fdSocket->fd_array[i];
        }
    }

    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _select
 * Signature: (JJJI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1select(
    JNIEnv *env, jclass clazz, jlong readFds, jlong writeFds, jlong exceptionFds, jint waitTimeout)
{

    timeval *wTime = new timeval{};
    if (waitTimeout == 0)
    {
        // delete wTime;
        wTime = nullptr;
    }
    else
    {
        wTime->tv_sec = waitTimeout / 1000;
        wTime->tv_usec = waitTimeout % 1000;
    }

    // int len = env->GetArrayLength(readFds);
    // jlong * c_read_fds = env->GetLongArrayElements(readFds, nullptr);
    // fd_set rfds;
    // FD_ZERO(&rfds);
    // for (int i = 0; i < len; ++i) {
    //     FD_SET(c_read_fds[i], &rfds);
    // }
    // return select(0, (fd_set *)readFds, (fd_set *)writeFds, (fd_set *)exceptionFds, &wTime);
    fd_set *rfds = (fd_set *)readFds;
    printf("rfds addr: %p\n", rfds);
    int ret = select(sizeof(((fd_set *)readFds)) * 8, (fd_set *)readFds, nullptr, nullptr, wTime);
    printf("retval %d\n", ret);
    delete wTime;

    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_create_event
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1create_1event(
    JNIEnv *env, jclass clazz)
{
    return reinterpret_cast<jlong>(WSACreateEvent());
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_reset_event
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1reset_1event(
    JNIEnv *env, jclass clazz, jlong event)
{
    return static_cast<jboolean>(WSAResetEvent((HANDLE)event));
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_close_event
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1close_1event(
    JNIEnv *env, jclass clazz, jlong event)
{
    return static_cast<jboolean>(WSACloseEvent((HANDLE)event));
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_wait_for_multiple_events
 * Signature: (I[Ljava/lang/Long;ZIZ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1wait_1for_1multiple_1events(
    JNIEnv *env, jclass clazz, jint count, jlongArray eventArray, jboolean wait, jint timeout, jboolean alertable)
{
    int len = env->GetArrayLength(eventArray);
    jlong *array = env->GetLongArrayElements(eventArray, FALSE);
    WSAEVENT *events = new WSAEVENT[len];
    for (int i = 0; i < len; ++i)
    {
        events[i] = (WSAEVENT)array[i];
    }
    env->ReleaseLongArrayElements(eventArray, array, 0);
    int ret = WSAWaitForMultipleEvents(count, events, wait, timeout, alertable);
    delete events;

    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_event_select
 * Signature: (JJJ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1event_1select(
    JNIEnv *env, jclass clazz, jlong socket, jlong event, jlong netEvent)
{
    return WSAEventSelect(static_cast<SOCKET>(socket), (WSAEVENT)event, (long)netEvent);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_enum_network_events
 * Signature: (JJ[B[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1enum_1network_1events(
    JNIEnv *env, jclass clazz, jlong socket, jlong event, jbyteArray bufForLong, jbyteArray bufForInt)
{
    WSANETWORKEVENTS e;
    int ret = WSAEnumNetworkEvents(static_cast<SOCKET>(socket), (WSAEVENT)event, &e);

    int len = env->GetArrayLength(bufForLong);
    char *long_buf = new char[len];
    for (auto i = 0; i < len; i++)
    {
        long_buf[i] = ((e.lNetworkEvents >> (8 * i)) & 0XFF);
    }
    env->SetByteArrayRegion(bufForLong, 0, len, reinterpret_cast<jbyte *>(long_buf));
    delete long_buf;

    len = env->GetArrayLength(bufForInt);
    char *int_buf = new char[len];
    for (auto i = 0; i < len / 4; i++)
    {
        for (auto j = 0; j < 4; ++j)
        {
            int_buf[i * 4 + j] = ((e.iErrorCode[i] >> (8 * j)) & 0XFF);
        }
    }
    env->SetByteArrayRegion(bufForInt, 0, len, reinterpret_cast<jbyte *>(int_buf));
    delete int_buf;

    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_socket
 * Signature: (IIII)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1socket(
    JNIEnv *env, jclass clazz, jint af, jint type, jint protocol, jint flag)
{
    return (jlong)WSASocket(af, type, protocol, nullptr, 0, flag);
}

#define TIMEOUT_VAL 100

// self defined completion key
typedef struct _io_op_head
{
    SOCKET socket;
    char *address;
    int port;
} io_op_head_s;

io_op_head_s *create_op_head(JNIEnv *env, SOCKET socket, jstring address, int port)
{
    io_op_head_s *ret = new io_op_head_s{};
    int len = env->GetStringUTFLength(address);
    const char *c_addr = env->GetStringUTFChars(address, nullptr);
    ret->address = new char[len];
    memcpy(ret->address, c_addr, len);
    env->ReleaseStringUTFChars(address, c_addr);
    ret->socket = socket;
    ret->port = port;
    return ret;
}

void destroy_op_head(io_op_head_s *head)
{
    if (head != nullptr)
    {
        delete head->address;
        delete head;
    }
}

typedef enum _io_op_type {
    IO_OP_READ = 0,
    IO_OP_WRITE = 1,
    IO_OP_CLOSE = 2,
    IO_OP_ERROR = 3,
} io_op_type_e;

// self defined overlapped
typedef struct _io_op_body
{
    OVERLAPPED overlapped; // overlapped
    WSAEVENT event;        // event
    io_op_type_e opType;   // operation type
    char *buf;             // actual buffer
    int len;               // buffer size
} io_op_body_s;

static JavaVM *jvm;
static jclass mCompletionPortModelClass;
static jmethodID mOnMessageMethod;

io_op_body_s *create_op_body(int size, io_op_type_e opType)
{
    io_op_body_s *ret = new io_op_body_s{};
    ret->buf = new char[size];
    ret->opType = opType;
    return ret;
}

void destroy_op_body(io_op_body_s *op_body)
{
    if (op_body != nullptr)
    {
        delete op_body->buf;
        delete op_body;
    }
}

/*
 * 服务线程 
 */
DWORD WINAPI ServerWorkerThread(LPVOID cp)
{
    DWORD count = 0;
    io_op_head_s *op_head;
    io_op_body_s *op_body;
    while (TRUE)
    {
        count = 0;
        op_body = nullptr;
        if (GetQueuedCompletionStatus((HANDLE)cp, &count, (PULONG_PTR)&op_head,
                                      (LPOVERLAPPED *)&op_body, TIMEOUT_VAL))
        {
            // success
            JNIEnv *g_env;
            jvm->AttachCurrentThread((void **)&g_env, NULL);
            if (g_env == NULL || mCompletionPortModelClass == NULL || mOnMessageMethod == 0)
            {
                jvm->DetachCurrentThread();
                continue;
            }

            if (count == 0)
            {
                printf("[NET] closed\n");
                // connection closed
                g_env->CallStaticVoidMethod(mCompletionPortModelClass,
                                            mOnMessageMethod, (jlong)cp,
                                            (jlong)op_head, (jint)IO_OP_CLOSE, nullptr);
                jvm->DetachCurrentThread();
                continue;
            }
            else
            {
                printf("[NET] event %d\n", op_body->opType);
                jbyteArray ret = g_env->NewByteArray(count);
                g_env->SetByteArrayRegion(ret, 0, count, reinterpret_cast<jbyte *>(op_body->buf));
                g_env->CallStaticVoidMethod(mCompletionPortModelClass,
                                            mOnMessageMethod, (jlong)cp,
                                            (jlong)op_head, (jint)op_body->opType, ret);
                jvm->DetachCurrentThread();

                // destroy_op_body(op_body);
            }
        }

        // failed
        DWORD err = GetLastError();
        if (err == WAIT_TIMEOUT)
        {
            // timeout, that's ok
            // printf("[NET] wait timeout");
            continue;
        }
        else if (op_body != nullptr)
        {
            // io error, oops
            // destroy_op_body(op_body);
            
            JNIEnv *g_env;
            jvm->AttachCurrentThread((void **)&g_env, NULL);
            printf("[NET] error %d\n", err);
            if (g_env == NULL || mCompletionPortModelClass == NULL || mOnMessageMethod == 0)
            {
                jvm->DetachCurrentThread();
                continue;
            }
            g_env->CallStaticVoidMethod(mCompletionPortModelClass,
                                        mOnMessageMethod, (jlong)cp,
                                        (jlong)op_head,
                                        (jint)IO_OP_ERROR, nullptr);
            jvm->DetachCurrentThread();
        }
        else
        {
            // other error, ooooooops
            printf("fatal error, exit thread: %d", err);
            break;
        }
    }
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_recv
 * Signature: (J[BJ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1recv(
    JNIEnv *env, jclass clazz, jlong socket, jint bufSize, jlong overlapped)
{
    io_op_body_s *op_body = create_op_body(bufSize, IO_OP_READ);

    WSABUF buf;
    buf.buf = op_body->buf;
    buf.len = bufSize;

    DWORD flag = 0;
    return WSARecv(static_cast<SOCKET>(socket), &buf, 1, nullptr, &flag, &op_body->overlapped, nullptr);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_send
 * Signature: (J[BJ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1send(
    JNIEnv *env, jclass clazz, jlong socket, jbyteArray sendBuf, jlong overlapped)
{
    io_op_body_s *op_body = create_op_body(0, IO_OP_WRITE);

    int len = env->GetArrayLength(sendBuf);
    WSABUF buf;
    buf.buf = new char[len];
    buf.len = len;
    env->GetByteArrayRegion(sendBuf, 0, len, reinterpret_cast<jbyte *>(buf.buf));

    DWORD flag = 0;
    return WSASend(static_cast<SOCKET>(socket), &buf, 1, nullptr, flag, &op_body->overlapped, nullptr);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_completion_key
 * Signature: (JLjava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1completion_1key(
    JNIEnv *env, jclass clazz, jlong socket, jstring address, jint port)
{
    return (jlong)create_op_head(env, (SOCKET)socket, address, port);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _destroy_completion_key
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1destroy_1completion_1key(
    JNIEnv *env, jclass clazz, jlong ptr)
{
    destroy_op_head((io_op_head_s *)ptr);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_wsa_overlapped
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1wsa_1overlapped(
    JNIEnv *env, jclass clazz, jlong evnet)
{
    return (jlong)create_op_body(0, IO_OP_READ);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_get_overlapped_result
 * Signature: (JJIZJ)Z
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1get_1overlapped_1result(
    JNIEnv *env, jclass clazz, jlong socket, jlong overlapped, jboolean wait, jlong flag)
{
    io_op_body_s *body = (io_op_body_s *) overlapped;
    DWORD count = 0;
    if (WSAGetOverlappedResult(static_cast<SOCKET>(socket), &body->overlapped, &count, wait, reinterpret_cast<PDWORD>(flag)))
    {
        return count;
    }
    return -1;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_iocp
 * Signature: (JJJI)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1iocp(
    JNIEnv *env, jclass clazz, jlong socket, jlong otherCP, jlong completionKey)
{
    HANDLE ret = 0;
    if (socket == 0)
    {
        ret = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
    }
    else
    {
        ret = CreateIoCompletionPort((HANDLE)socket, (HANDLE)otherCP, (ULONG_PTR)completionKey, 0);
    }
    return (jlong)ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_server_thread
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1server_1thread(
    JNIEnv *env, jclass clazz, jlong cp)
{
    env->GetJavaVM(&jvm);

    mCompletionPortModelClass = (jclass)env->NewGlobalRef(
        env->FindClass("com/github/jeffreystoke/winsock/io/model/CompletionPortModel"));
    mOnMessageMethod = env->GetStaticMethodID(mCompletionPortModelClass, "onMessage", "(JJI[B)V");

    HANDLE thread;
    DWORD thread_id;
    if ((thread = CreateThread(nullptr, 0,
                               ServerWorkerThread,
                               (LPVOID)cp,
                               0, &thread_id)) == nullptr)
    {
        return GetLastError();
    }
    CloseHandle(thread);
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _cancel_io
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1cancel_1io(
    JNIEnv *env, jclass clazz, jlong socket)
{
    return CancelIo((HANDLE)socket);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _post_queued_completion_status
 * Signature: (JIJJ)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1post_1queued_1completion_1status(
    JNIEnv *env, jclass clazz, jlong socket, jint count, jlong completionKey, jlong overlapped)
{
    return PostQueuedCompletionStatus((HANDLE)socket, count, (ULONG_PTR)completionKey, (LPOVERLAPPED)overlapped);
}

#ifdef __cplusplus
}
#endif
#endif
