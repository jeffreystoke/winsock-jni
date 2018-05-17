package com.github.jeffreystoke.winsock.io.constant

enum class SocketFlag(val value: Int) {
    WSA_FLAG_OVERLAPPED(0x01),
    WSA_FLAG_MULTIPOINT_C_ROOT(0x02),
    WSA_FLAG_MULTIPOINT_C_LEAF(0x04),
    WSA_FLAG_MULTIPOINT_D_ROOT(0x08),
    WSA_FLAG_MULTIPOINT_D_LEAF(0x10),
    WSA_FLAG_ACCESS_SYSTEM_SECURITY(0x40),
    WSA_FLAG_NO_HANDLE_INHERIT(0x80),
    WSA_FLAG_REGISTERED_IO(0x100),
}