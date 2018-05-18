package com.github.jeffreystoke.winsock.examples;

import com.github.jeffreystoke.winsock.io.struct.Socket;

public abstract class Server extends Thread {

    protected Socket mServerSocket = new Socket();

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
