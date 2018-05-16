#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <Mswsock.h>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <jni.h>
#include <WS2tcpip.h>

#include "winsock_jni.h"

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
    free(reinterpret_cast<void *>(ptr));
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaStartup
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
 * Method:    _wsaCleanup
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
 * Method:    _wsaGetLastError
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
    int len = env->GetArrayLength(optVal);
    auto *buf = new char[len];
    env->GetByteArrayRegion(optVal, 0, len, reinterpret_cast<jbyte *>(buf));

    return setsockopt((SOCKET)socket, level, optKey, buf, len);
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
    auto *buf = new char[len];
    int ret = getsockopt(static_cast<SOCKET>(socket), level, optKey, buf, &len);
    // jbyteArray array = env->NewByteArray(len);
    env->SetByteArrayRegion(retBuf, 0, len, reinterpret_cast<jbyte *>(buf));
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
    const char *addr = env->GetStringUTFChars(address, nullptr);
    sin.sin_addr.s_addr = inet_addr(addr);

    bind((SOCKET)socket, (LPSOCKADDR)&sin, sizeof(sin));
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
    return listen((SOCKET)socket, backlog);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _accept
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1accept(
    JNIEnv *env, jclass clazz, jlong socket)
{

    sockaddr_in sin{};
    int len = sizeof(sin);
    return accept(static_cast<SOCKET>(socket), reinterpret_cast<sockaddr *>(&sin), &len);
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
    int ret = recv((SOCKET)socket, buf, len, flag);
    env->SetByteArrayRegion(recvBuf, 0, len, reinterpret_cast<jbyte *>(buf));
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
    return send((SOCKET)socket, buf, len, flag);
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
    const char *addr = env->GetStringUTFChars(rAddress, nullptr);
    sin.sin_addr.s_addr = inet_addr(addr);

    return connect(static_cast<SOCKET>(socket), reinterpret_cast<const sockaddr *>(&sin), sizeof(sin));
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _recvFrom
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1recv_1from(
    JNIEnv *env, jclass clazz, jlong socket, jbyteArray buf, jint flag)
{
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _sendTo
 * Signature: (J[BILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1send_1to(
    JNIEnv *env, jclass clazz, jlong socket, jbyteArray buf, jint flag, jstring rAddress)
{
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _createFdSet
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1fd_1set(
    JNIEnv *env, jclass clazz)
{
    auto *fdSet = static_cast<fd_set *>(malloc(sizeof(fd_set)));
    FD_ZERO(fdSet);
    return (jlong)fdSet;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _addFd
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
 * Method:    _removeFd
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1remove_1fd(
    JNIEnv *env, jclass clazz, jlong fdset, jlong socket)
{
    FD_CLR((SOCKET)socket, (fd_set *)fdset);
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
    timeval wTime{};
    wTime.tv_sec = waitTimeout / 1000;
    wTime.tv_usec = (waitTimeout - wTime.tv_sec * 1000) / 100;
    return select(0, (fd_set *)readFds, (fd_set *)writeFds, (fd_set *)exceptionFds, &wTime);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaCreateEvent
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
 * Method:    _wsaResetEvent
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
 * Method:    _wsaCloseEvent
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
 * Method:    _wsaWaitForMultipleEvents
 * Signature: (I[Ljava/lang/Long;ZIZ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1wait_1for_1multiple_1events(
    JNIEnv *env, jclass clazz, jint count, jobjectArray eventArray, jboolean wait, jint timeout, jboolean alertable)
{
    auto len = env->GetArrayLength(eventArray);
    auto events = new WSAEVENT[len];
    for (int i = 0; i < len; ++i)
    {
        auto element = (jlong)evn->GetObjectArrayElement(eventArray, i);
        events[i] = (WSAEVENT)element;
    }

    return WSAWaitForMultipleEvents(count, events, wait, timeout, alertable);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaEventSelect
 * Signature: (JJJ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1event_1select(
    JNIEnv *env, jclass clazz, jlong socket, jlong event, jlong netEvent)
{
    return WSAEventSelect((SOCKET)socket, (WSAEVENT)event, (long)netEvent);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaEnumNetworkEvents
 * Signature: (JJ[B[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1enum_1network_1events(
    JNIEnv *env, jclass clazz, jlong socket, jlong event, jbyteArray bufForLong, jbyteArray bufForInt)
{
    WSANETWORKEVENTS e;
    auto ret = WSAEnumNetworkEvents((SOCKET)socket, (WSAEVENT)event, &e);

    auto len = env->GetArrayLength(bufForLong);
    auto long_buf = new char[len];
    for (auto i = 0; i < len; i++)
    {
        long_buf[i] = ((e.lNetworkEvents >> (8 * i)) & 0XFF);
    }
    env->SetByteArrayRegion(bufForLong, 0, len, reinterpret_cast<jbyte *>(long_buf));

    e.iErrorCode auto len = env->GetArrayLength(bufForInt);
    auto int_buf = new char[len];
    for (auto i = 0; i < len / 4; i++)
    {
        for (auto j = 0; j < 4; ++j)
        {
            int_buf[i * 4 + j] = ((e.iErrorCode[i] >> (8 * j)) & 0XFF);
        }
    }
    env->SetByteArrayRegion(bufForInt, 0, len, reinterpret_cast<jbyte *>(int_buf));

    return ret
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_connect
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1connect(
    JNIEnv *env, jclass clazz)
{
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_accept
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1accept(
    JNIEnv *env, jclass clazz, jlong socket)
{
    return 0l;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaSocket
 * Signature: (IIII)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1socket(
    JNIEnv *env, jclass clazz, jint, jint, jint, jint)
{
    return 0l;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaRecv
 * Signature: (J[[BIIJ)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1recv(
    JNIEnv *env, jclass clazz, jlong, jobjectArray, jint, jint, jlong)
{
    return;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaRecvFrom
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1recv_1from(
    JNIEnv *env, jclass clazz)
{
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaSend
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1send(
    JNIEnv *env, jclass clazz)
{
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaSendTo
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1send_1to(
    JNIEnv *env, jclass clazz)
{
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_CompletionKey
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1completion_1key(
    JNIEnv *env, jclass clazz, jlong, jstring)
{
    return 0l;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _createWSAOverlapped
 * Signature: (IIIIJ)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1wsa_1overlapped(
    JNIEnv *env, jclass clazz, jint, jint, jint, jint, jlong)
{
    return 0l;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaGetOverlappedResult
 * Signature: (JJZJ)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1get_1overlapped_1result(
    JNIEnv *env, jclass clazz, jlong, jlong, jboolean, jlong)
{
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _createIOCP
 * Signature: (JJJI)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1iocp(
    JNIEnv *env, jclass clazz, jlong, jlong, jlong, jint)
{
    return 0l;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _getQueuedCompletionStatus
 * Signature: (JIJJI)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1get_1queued_1completion_1status(
    JNIEnv *env, jclass clazz, jlong, jint, jlong, jlong, jint)
{
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _cancelIO
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1cancel_1io(
    JNIEnv *env, jclass clazz, jlong)
{
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _postQueuedCompletionStatus
 * Signature: (JIJJ)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1post_1queued_1completion_status(
    JNIEnv *env, jclass clazz, jlong, jint, jlong, jlong)
{
    return 0;
}

#ifdef __cplusplus
}
#endif
#endif
