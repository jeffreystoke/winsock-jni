#include <Winsock2.h>

#include "winsock_jni.h"

#ifndef _Included_com_github_jeffreystoke_winsock_io_internal_JavaWinSock
#define _Included_com_github_jeffreystoke_winsock_io_internal_JavaWinSock
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1free
(JNIEnv *, jclass, jlong ptr) {
    GlobalFree(ptr);
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaStartup
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaStartup
(JNIEnv *env, jclass) {
    WSADATA wsaData;
    WORD sockVersion = MAKEWORD(minorVer, majorVer);

    if (WSAStartup(sockVersion, &wsaData) != 0) {
        return env->NewStringUTF("ERROR init winsock lib");
    }

    return null;
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaCleanup
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaCleanup
(JNIEnv *, jclass) {
    WSACleanup();
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaGetLastError
 * Signature: ()I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaGetLastError
(JNIEnv *, jclass) {
    return WSAGetLastError();
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _setsockopt
 * Signature: (JII[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1setsockopt
(JNIEnv *, jclass, jlong, jint, jint, jbyteArray) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _getsockopt
 * Signature: (JII[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1getsockopt
(JNIEnv *, jclass, jlong, jint, jint, jbyteArray) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _ioctlsocket
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1ioctlsocket
(JNIEnv *, jclass, jlong, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _socket
 * Signature: (III)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1socket
(JNIEnv *, jclass, jint, jint, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _bind
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1bind
(JNIEnv *, jclass, jlong, jstring, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _listen
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1listen
(JNIEnv *, jclass, jlong, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _accept
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1accept
(JNIEnv *, jclass, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _recv
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1recv
(JNIEnv *, jclass, jlong, jbyteArray, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _send
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1send
(JNIEnv *, jclass, jlong, jbyteArray, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _closesocket
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1closesocket
(JNIEnv *, jclass, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _shutdown
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1shutdown
(JNIEnv *, jclass, jlong, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _connect
 * Signature: (JLjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1connect
(JNIEnv *, jclass, jlong, jstring, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _recvFrom
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1recvFrom
(JNIEnv *, jclass, jlong, jbyteArray, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _sendTo
 * Signature: (J[BILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1sendTo
(JNIEnv *, jclass, jlong, jbyteArray, jint, jstring) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _createFdSet
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1createFdSet
(JNIEnv *, jclass) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _addFd
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1addFd
(JNIEnv *, jclass, jlong, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _removeFd
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1removeFd
(JNIEnv *, jclass, jlong, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _getSetFd
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1getSetFd
(JNIEnv *, jclass, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _select
 * Signature: (JJJI)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1select
(JNIEnv *, jclass, jlong, jlong, jlong, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _createWindow
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1createWindow
(JNIEnv *, jobject) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaAsyncSelect
 * Signature: (JJIJ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaAsyncSelect
(JNIEnv *, jclass, jlong, jlong, jint, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaGetSelectError
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaGetSelectError
(JNIEnv *, jobject, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaGetSelectEvent
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaGetSelectEvent
(JNIEnv *, jobject, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaCreateEvent
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaCreateEvent
(JNIEnv *, jclass) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaResetEvent
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaResetEvent
(JNIEnv *, jclass, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaCloseEvent
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaCloseEvent
(JNIEnv *, jclass, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaWaitForMultipleEvents
 * Signature: (I[Ljava/lang/Long;ZIZ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaWaitForMultipleEvents
(JNIEnv *, jclass, jint, jobjectArray, jboolean, jint, jboolean) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaEventSelect
 * Signature: (JJJ)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaEventSelect
(JNIEnv *, jclass, jlong, jlong, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaEnumNetworkEvents
 * Signature: (JJ[B)I
 */
JNIEXPORT jint JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaEnumNetworkEvents
(JNIEnv *, jclass, jlong, jlong, jbyteArray) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsa_connect
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1connect
(JNIEnv *, jclass) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsa_accept
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsa_1accept
(JNIEnv *, jclass, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaSocket
 * Signature: (IIII)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaSocket
(JNIEnv *, jclass, jint, jint, jint, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaRecv
 * Signature: (J[[BIIJ)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaRecv
(JNIEnv *, jclass, jlong, jobjectArray, jint, jint, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaRecvFrom
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaRecvFrom
(JNIEnv *, jclass) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaSend
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaSend
(JNIEnv *, jclass) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaSendTo
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaSendTo
(JNIEnv *, jclass) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _create_CompletionKey
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1create_1CompletionKey
(JNIEnv *, jclass, jlong, jstring) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _createWSAOverlapped
 * Signature: (IIIIJ)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1createWSAOverlapped
(JNIEnv *, jclass, jint, jint, jint, jint, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _wsaGetOverlappedResult
 * Signature: (JJZJ)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1wsaGetOverlappedResult
(JNIEnv *, jclass, jlong, jlong, jboolean, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _createIOCP
 * Signature: (JJJI)J
 */
JNIEXPORT jlong JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1createIOCP
(JNIEnv *, jclass, jlong, jlong, jlong, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _getQueuedCompletionStatus
 * Signature: (JIJJI)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1getQueuedCompletionStatus
(JNIEnv *, jclass, jlong, jint, jlong, jlong, jint) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _cancelIO
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1cancelIO
(JNIEnv *, jclass, jlong) {
}

/*
 * Class:     com_github_jeffreystoke_winsock_io_internal_JavaWinSock
 * Method:    _postQueuedCompletionStatus
 * Signature: (JIJJ)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_github_jeffreystoke_winsock_io_internal_WinSock__1postQueuedCompletionStatus
(JNIEnv *, jclass, jlong, jint, jlong, jlong) {
}

#ifdef __cplusplus
}
#endif
#endif
