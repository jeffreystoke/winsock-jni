package com.github.jeffreystoke.winsock.io.internal

import com.github.jeffreystoke.winsock.io.constant.ShutdownOption
import com.github.jeffreystoke.winsock.io.struct.Socket
import org.junit.jupiter.api.AfterEach
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test


class SocketTest {

    private val sListenAddress = "127.0.0.1"
    private val sListenPort = 4567

    private lateinit var mServerSocket: Socket
    private lateinit var mSocket: Socket

    @BeforeEach
    fun init() {
        mServerSocket = Socket()
        mSocket = Socket()

        mServerSocket.bind(sListenAddress, sListenPort)
        mServerSocket.listen(0)
    }

    @AfterEach
    fun cleanup() {
        mSocket.close()
        mSocket.destroy()

        mServerSocket.close()
        mServerSocket.destroy()

        WinSock._wsa_cleanup()
    }

    @Test
    fun connectTest() {
    }

    @Test
    fun sendTest() {
    }

    @Test
    fun recvTest() {
    }

    @Test
    fun acceptTest() {
    }

    @Test
    fun shutdownTest() {
    }

    @Test
    fun closeTest() {
    }

    @Test
    fun getOptionTest() {
    }

    @Test
    fun setOptionTest() {
    }
}