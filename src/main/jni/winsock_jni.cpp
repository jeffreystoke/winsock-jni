#include <Winsock2.h>
#include <Mswsock.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>

#include "winsock_jni.h"

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
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1free
(JNIEnv *env, jclass clazz, jlong ptr) {
    free((HGLOBAL) ptr);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaStartup
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaStartup
(JNIEnv *env, jclass) {
    WSADATA wsaData;
    WORD sockVersion = MAKEWORD(2, 2);

    if (WSAStartup(sockVersion, &wsaData) != 0) {
        return env->NewStringUTF("ERROR init winsock lib");
    }

    return NULL;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaCleanup
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaCleanup
(JNIEnv *env, jclass) {
    WSACleanup();
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaGetLastError
 * Signature: ()I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaGetLastError
(JNIEnv *env, jclass) {
    return WSAGetLastError();
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _setsockopt
 * Signature: (JII[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1setsockopt
(JNIEnv *env, jclass clazz, jlong socket, jint level, jint optKey,
 jbyteArray optVal) {
    int len = env->GetArrayLength(optVal);
    char *buf = new char[len];
    env->GetByteArrayRegion(optVal, 0, len, reinterpret_cast<jbyte *>(buf));

    return setsockopt((SOCKET) socket, level, optKey, buf, len);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _getsockopt
 * Signature: (JII[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1getsockopt
(JNIEnv *env, jclass clazz, jlong socket, jint level, jint optKey,
 jbyteArray retBuf) {
    int len = env->GetArrayLength(retBuf);
    char *buf = new char[len];
    int ret = getsockopt((SOCKET) socket, level, optKey, buf, &len);
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
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1ioctlsocket
(JNIEnv *env, jclass clazz, jlong socket, jint mode) {

}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _socket
 * Signature: (III)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1socket
(JNIEnv *env, jclass clazz, jint af, jint sockType, jint proto) {
    return socket(af, sockType, proto);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _bind
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1bind
(JNIEnv *env, jclass clazz, jlong socket, jstring address, jint port) {

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = (u_short) htons(port);
    const char *addr = env->GetStringUTFChars(address, 0);
    sin.sin_addr.s_addr = inet_addr(addr);

    bind((SOCKET) socket, (LPSOCKADDR) &sin, sizeof(sin));
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _listen
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1listen
(JNIEnv *env, jclass clazz, jlong socket, jint backlog) {
    return listen((SOCKET) socket, backlog);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _accept
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1accept
(JNIEnv *env, jclass clazz, jlong socket) {

    sockaddr_in sin;
    int len = sizeof(sin);
    return accept((SOCKET) socket, (SOCKADDR *) &sin, &len);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _recv
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1recv
(JNIEnv *env, jclass clazz, jlong socket, jbyteArray recvBuf, jint flag) {
    int len = env->GetArrayLength(recvBuf);
    char *buf = new char[len];
    int ret = recv((SOCKET) socket, buf, len, flag);
    env->SetByteArrayRegion(recvBuf, 0, len, reinterpret_cast<jbyte *>(buf));
    return ret;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _send
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1send
(JNIEnv *env, jclass clazz, jlong socket, jbyteArray sendBuf, jint flag) {
    int len = env->GetArrayLength(sendBuf);
    char *buf = new char[len];
    env->GetByteArrayRegion(sendBuf, 0, len, reinterpret_cast<jbyte *>(buf));
    return send((SOCKET) socket, buf, len, flag);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _closesocket
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1closesocket
(JNIEnv *env, jclass clazz, jlong socket) {
    return closesocket((SOCKET) socket);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _shutdown
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1shutdown
(JNIEnv *env, jclass clazz, jlong socket, jint method) {
    return shutdown((SOCKET) socket, method);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _connect
 * Signature: (JLjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1connect
(JNIEnv *env, jclass clazz, jlong socket, jstring rAddress, jint port) {

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    const char *addr = env->GetStringUTFChars(rAddress, 0);
    sin.sin_addr.s_addr = inet_addr(addr);

    return connect((SOCKET) socket, (LPSOCKADDR) &sin, sizeof(sin));
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _recvFrom
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1recvFrom
(JNIEnv *env, jclass clazz, jlong socket, jbyteArray buf, jint flag) {
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _sendTo
 * Signature: (J[BILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1sendTo
(JNIEnv *env, jclass clazz, jlong socket, jbyteArray buf, jint flag,
 jstring rAddress) {
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _createFdSet
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1createFdSet
(JNIEnv *env, jclass clazz) {
    fd_set *fdSet = (fd_set *) malloc(sizeof(fd_set));
    FD_ZERO(fdSet);
    return (jlong) fdSet;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _addFd
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1addFd
(JNIEnv *env, jclass clazz, jlong fdset, jlong socket) {
    FD_SET((SOCKET) socket, (fd_set *) fdset);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _removeFd
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1removeFd
(JNIEnv *env, jclass clazz, jlong fdset, jlong socket) {
    FD_CLR((SOCKET) socket, (fd_set *) fdset);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _getSetFd
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1getSetFd
(JNIEnv *env, jclass clazz, jlong fdset) {
    fd_set* fdSocket = (fd_set *) fdset;

    for (int i = 0; i < (int) fdSocket->fd_count; i++) {
        if (FD_ISSET(fdSocket->fd_array[i], fdSocket)) {
            return (jlong) fdSocket->fd_array[i];
        }
    }

    return NULL;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _select
 * Signature: (JJJI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1select
(JNIEnv *env, jclass clazz, jlong readFds, jlong writeFds, jlong exceptionFds,
 jint waitTimeout) {
    timeval wTime;
    wTime.tv_sec = waitTimeout / 1000;
    wTime.tv_usec = (waitTimeout - wTime.tv_sec *1000) / 100;
    return select(0, (fd_set*) readFds, (fd_set*) writeFds, (fd_set*) exceptionFds, &wTime);
}

static JavaVM *jvm;
static jclass wsaAsyncClass;
static jmethodID wsaAsnycCallback;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
    switch (uMsg) {
    case 1025: {
        JNIEnv *g_env;
        jvm->AttachCurrentThread((void **)&g_env, NULL);
        g_env->CallStaticVoidMethod(wsaAsyncClass, wsaAsnycCallback,
                                    (jlong) wParam, (jlong)lParam);
        break;
    }

    case WM_DESTROY: {
        PostQuitMessage(0) ;
        return 0;
    }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _createWindow
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1createWindow
(JNIEnv *env, jobject jobj) {
    WNDCLASSEX wndclass;

    // 用描述主窗口的参数填充WNDCLASSEX结构
    wndclass.cbSize = sizeof(wndclass);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WindowProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = NULL;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = "HIDDEN" ;
    wndclass.hIconSm = NULL;
    RegisterClassEx(&wndclass);
    // 创建主窗口

    HWND hwnd = CreateWindowEx(0, "HIDDEN", "", WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, CW_USEDEFAULT,
                              CW_USEDEFAULT, CW_USEDEFAULT,
                              NULL, NULL, NULL, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    env->GetJavaVM(&jvm);
    wsaAsyncClass = (jclass)env->NewGlobalRef(
                        env->FindClass("com/github/jeffreystoke/winsock/io/model/WSAAsyncSelect"));

    wsaAsnycCallback = env->GetStaticMethodID(wsaAsyncClass, "_onMessage", "(JJ)V");
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaAsyncSelect
 * Signature: (JJIJ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaAsyncSelect
(JNIEnv *env, jclass clazz, jlong socket, jlong hwnd, jint msgNum,
 jlong netEvent) {
    return WSAAsyncSelect((SOCKET) socket, (HWND) hwnd, msgNum, netEvent);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaGetSelectError
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaGetSelectError
(JNIEnv *env, jobject, jlong lParam) {
    return WSAGETSELECTERROR(lParam);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaGetSelectEvent
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaGetSelectEvent
(JNIEnv *env, jobject, jlong lParam) {
    return WSAGETSELECTEVENT(lParam);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaCreateEvent
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaCreateEvent
(JNIEnv *env, jclass clazz) {
    return (jlong) WSACreateEvent();
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaResetEvent
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaResetEvent
(JNIEnv *env, jclass clazz, jlong event) {
    return (jboolean) WSAResetEvent((HANDLE) event);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaCloseEvent
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaCloseEvent
(JNIEnv *env, jclass clazz, jlong event) {
    return (jboolean) WSACloseEvent((HANDLE) event);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaWaitForMultipleEvents
 * Signature: (I[Ljava/lang/Long;ZIZ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaWaitForMultipleEvents
(JNIEnv *env, jclass clazz, jint count, jobjectArray eventArray, jboolean wait,
 jint timeout, jboolean alertable) {
    // TODO get array elements
//    return WSAWaitForMultipleEvents(count, , wait, timeout, alertable);
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaEventSelect
 * Signature: (JJJ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaEventSelect
(JNIEnv *env, jclass clazz, jlong socket, jlong event, jlong netEvent) {
    return WSAEventSelect((SOCKET) socket, (WSAEVENT) event, netEvent);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaEnumNetworkEvents
 * Signature: (JJ[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaEnumNetworkEvents
(JNIEnv *env, jclass clazz, jlong socket, jlong event, jbyteArray bufForLong) {
    WSANETWORKEVENTS e;
    return WSAEnumNetworkEvents((SOCKET) socket, (WSAEVENT) event, &e);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_connect
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1connect
(JNIEnv *env, jclass) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsa_accept
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1accept
(JNIEnv *env, jclass clazz, jlong) {
    return 0l;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaSocket
 * Signature: (IIII)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaSocket
(JNIEnv *env, jclass clazz, jint, jint, jint, jint) {
    return 0l;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaRecv
 * Signature: (J[[BIIJ)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaRecv
(JNIEnv *env, jclass clazz, jlong, jobjectArray, jint, jint, jlong) {
    return;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaRecvFrom
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaRecvFrom
(JNIEnv *env, jclass) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaSend
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaSend
(JNIEnv *env, jclass) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaSendTo
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaSendTo
(JNIEnv *env, jclass) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _create_CompletionKey
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1CompletionKey
(JNIEnv *env, jclass clazz, jlong, jstring) {
    return 0l;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _createWSAOverlapped
 * Signature: (IIIIJ)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1createWSAOverlapped
(JNIEnv *env, jclass clazz, jint, jint, jint, jint, jlong) {
    return 0l;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _wsaGetOverlappedResult
 * Signature: (JJZJ)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaGetOverlappedResult
(JNIEnv *env, jclass clazz, jlong, jlong, jboolean, jlong) {
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _createIOCP
 * Signature: (JJJI)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1createIOCP
(JNIEnv *env, jclass clazz, jlong, jlong, jlong, jint) {
    return 0l;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _getQueuedCompletionStatus
 * Signature: (JIJJI)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1getQueuedCompletionStatus
(JNIEnv *env, jclass clazz, jlong, jint, jlong, jlong, jint) {
    return 0;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _cancelIO
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1cancelIO
(JNIEnv *env, jclass clazz, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_WinSock
 * Method:    _postQueuedCompletionStatus
 * Signature: (JIJJ)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1postQueuedCompletionStatus
(JNIEnv *env, jclass clazz, jlong, jint, jlong, jlong) {
    return 0;
}

#ifdef __cplusplus
}
#endif
#endif
