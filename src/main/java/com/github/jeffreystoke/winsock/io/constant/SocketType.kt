package com.github.jeffreystoke.winsock.io.constant

enum class SocketType(val value: Int) {
    Stream(1),
    Datagram(2),
    Raw(3),
    Rdm(4),
    SeqPacket(5)
}