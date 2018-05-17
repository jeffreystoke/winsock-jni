package com.github.jeffreystoke.winsock.io.constant

enum class ProtocolType(val value: Int) {
    IP(0),
    ICMP(1),
    IGMP(2),
    GGP(3),
    TCP(6),
    PUP(12),
    UDP(17),
    IDP(22),
    ND(77),
    RAW(255),
    MAX(256),
}