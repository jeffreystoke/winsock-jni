package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.internal.WinSock


object WSAUtils {

    fun wsaCleanup() = WinSock._wsa_cleanup()

    fun wsaGetLastError() = WinSock._wsa_get_last_error()
}