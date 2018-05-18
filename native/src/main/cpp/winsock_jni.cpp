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
    FD_SET(static_cast<SOCKET>(socket), (fd_set *)fdset);
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
    timeval wTime{};
    wTime.tv_sec = waitTimeout / 1000;
    wTime.tv_usec = (waitTimeout - wTime.tv_sec * 1000) / 100;
    return select(0, (fd_set *)readFds, (fd_set *)writeFds, (fd_set *)exceptionFds, &wTime);
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

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_recv
 * Signature: (J[Ljava/lang/Long;IIJ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1recv(
    JNIEnv *env, jclass clazz, jlong socket, jlongArray recvBufs, jint count, jint flag, jlong overlapped)
{
    int len = env->GetArrayLength(recvBufs);
    jlong *array = env->GetLongArrayElements(recvBufs, FALSE);
    WSABUF *buf = new WSABUF[len];
    for (int i = 0; i < len; ++i)
    {
        buf[i] = *((WSABUF *)array[i]);
    }
    int ret = WSARecv(static_cast<SOCKET>(socket), buf, len, (LPDWORD)count, (LPDWORD)flag, (LPWSAOVERLAPPED)overlapped, nullptr);
    delete buf;
    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_send
 * Signature: (J[Ljava/lang/Long;IIJ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1send(
    JNIEnv *env, jclass clazz, jlong socket, jlongArray sendBufs, jint count, jint flag, jlong overlapped)
{
    int len = env->GetArrayLength(sendBufs);
    jlong *array = env->GetLongArrayElements(sendBufs, FALSE);
    WSABUF *buf = new WSABUF[len];
    for (int i = 0; i < len; ++i)
    {
        buf[i] = *((WSABUF *)array[i]);
    }
    int ret = WSASend(static_cast<SOCKET>(socket), buf, len, (LPDWORD)count, flag, (LPWSAOVERLAPPED)overlapped, nullptr);
    delete buf;
    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_wsa_buf
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1wsa_1buf(
    JNIEnv *env, jclass clazz, jint size)
{
    WSABUF *buf = new WSABUF{};
    buf->buf = new char[size];
    buf->len = (u_long)size;
    return (jlong)buf;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _destroy_wsa_buf
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1destroy_1wsa_1buf(
    JNIEnv *env, jobject obj, jlong buf)
{
    WSABUF *wsaBuf = (WSABUF *)buf;
    delete wsaBuf->buf;
    delete wsaBuf;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _get_wsa_buf
 * Signature: (J)V
 */
JNIEXPORT jbyteArray JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1get_1wsa_1buf(
    JNIEnv *env, jobject obj, jlong buf)
{
    WSABUF *wsaBuf = (WSABUF *)buf;
    auto ret = env->NewByteArray(wsaBuf->len);
    env->SetByteArrayRegion(ret, 0, wsaBuf->len, reinterpret_cast<jbyte *>(wsaBuf->buf));
    return ret;
}

typedef struct _completionKey
{
    SOCKET s;
    SOCKADDR_IN *remote_addr;
} COMPLETION_KEY;

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_completion_key
 * Signature: (JLjava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1completion_1key(
    JNIEnv *env, jclass clazz, jlong socket, jstring address, jint port)
{
    COMPLETION_KEY *key = new COMPLETION_KEY{};
    key->s = static_cast<SOCKET>(socket);
    sockaddr_in *sin = new sockaddr_in{};
    sin->sin_family = AF_INET;
    sin->sin_port = htons((u_short)port);
    auto addr = env->GetStringUTFChars(address, nullptr);
    sin->sin_addr.s_addr = inet_addr(addr);
    env->ReleaseStringUTFChars(address, addr);
    key->remote_addr = (SOCKADDR_IN *) sin;
    return (jlong)key;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_wsa_overlapped
 * Signature: (IIIIJ)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1wsa_1overlapped(
    JNIEnv *env, jclass clazz, jint internal, jint internalHigh, jint offset, jint offsetHigh, jlong evnet)
{
    WSAOVERLAPPED *o = new WSAOVERLAPPED{};
    o->Internal = internal;
    o->InternalHigh = internalHigh;
    o->Offset = offset;
    o->OffsetHigh = offsetHigh;
    return (jlong)o;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_get_overlapped_result
 * Signature: (JJIZJ)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1get_1overlapped_1result(
    JNIEnv *env, jclass clazz, jlong socket, jlong overlapped, jint count, jboolean wait, jlong flag)
{
    return WSAGetOverlappedResult(static_cast<SOCKET>(socket), (LPWSAOVERLAPPED)overlapped, reinterpret_cast<LPDWORD>(count), wait, reinterpret_cast<PDWORD>(flag));
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_iocp
 * Signature: (JJJI)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1iocp(
    JNIEnv *env, jclass clazz, jlong socket, jlong otherCP, jlong completionKey, jint threadCount)
{
    return (jlong)CreateIoCompletionPort((HANDLE)(ULONG_PTR)socket, (HANDLE)otherCP, (ULONG_PTR)completionKey, threadCount);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _get_queued_completion_status
 * Signature: (JIJJI)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1get_1queued_1completion_1status(
    JNIEnv *, jclass, jlong cp, jint count, jlong completionKey, jlong overlapped, jint waitTimeout)
{
    return GetQueuedCompletionStatus((HANDLE)cp, reinterpret_cast<LPDWORD>(count), reinterpret_cast<PULONG_PTR>(completionKey), (LPOVERLAPPED *)overlapped, waitTimeout);
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
