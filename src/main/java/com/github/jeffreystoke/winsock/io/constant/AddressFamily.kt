package com.github.jeffreystoke.winsock.io.constant

enum class AddressFamily(val value: Int) {
    UNIX(1),
    Internet(2),
    IMPLINK(3),
    PUP(4),
    CHAOS(5),
    NS(6),
    IPX(NS.value),
    ISO(7),
    OSI(ISO.value),
    ECMA(8),
    DATAKIT(9),
    CCITT(10),
    SNA(11),
    DECnet(12),
    DLI(13),
    LAT(14),
    HYLINK(15),
    APPLETALK(16),
    NETBIOS(17),
    VOICEVIEW(18),
    FIREFOX(19),
    UNKNOWN1(20),
    BAN(21),
    ATM(22),
    INET6(23),
    CLUSTER(24),
    IRDA(26),
    MAX(27),
}