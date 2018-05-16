package com.github.jeffreystoke.winsock.io.model

import com.github.jeffreystoke.winsock.io.struct.Socket
import org.junit.jupiter.api.Test


class SocketTest {

    private val sListenAddress = "127.0.0.1"
    private val sListenPort = 4567

    private val mServerSocket = Socket()
    private var mSocket = Socket()


    @Test
    fun connectTest() {
        mServerSocket.bind(sListenAddress, sListenPort)
        mServerSocket.listen(0)
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