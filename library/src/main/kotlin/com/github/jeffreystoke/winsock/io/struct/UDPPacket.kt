package com.github.jeffreystoke.winsock.io.struct

import java.util.*

data class UDPPacket(val address: String, val port: Int, val data: ByteArray) {

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as UDPPacket

        if (address != other.address) return false
        if (port != other.port) return false
        if (!Arrays.equals(data, other.data)) return false

        return true
    }

    override fun hashCode(): Int {
        var result = address.hashCode()
        result = 31 * result + port
        result = 31 * result + Arrays.hashCode(data)
        return result
    }
}