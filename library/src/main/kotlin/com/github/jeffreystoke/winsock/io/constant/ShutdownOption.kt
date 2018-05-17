package com.github.jeffreystoke.winsock.io.constant

enum class ShutdownOption(val value: Int) {
    Receive(0x00),
    Send(0x01),
    Both(0x02),
}