package com.github.jeffreystoke.winsock.examples;

import com.github.jeffreystoke.winsock.io.struct.WSASocket;

public abstract class WSAServer extends Thread {

    protected WSASocket mServerSocket = new WSASocket();

    protected abstract String getTag();

    protected void println(String... s) {
        System.out.println("[" + getTag() + "] " + String.join(" ", s));
    }

    @Override
    public void run() {
        mServerSocket.bind(Constants.sListenAddress, Constants.sListenPort);
        mServerSocket.listen();
    }
}
