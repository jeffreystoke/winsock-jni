package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.internal.WinSock


object WSAUtils {

    fun wsaCleanup() = WinSock._wsaCleanup()

    fun wsaGetLastError() = WinSock._wsaGetLastError()
}