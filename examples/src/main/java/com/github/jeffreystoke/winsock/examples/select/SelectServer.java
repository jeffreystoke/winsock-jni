package com.github.jeffreystoke.winsock.examples.select;

import com.github.jeffreystoke.winsock.examples.Constants;
import com.github.jeffreystoke.winsock.io.model.SelectModel;
import com.github.jeffreystoke.winsock.io.struct.Socket;

public class SelectServer extends Thread {

    private Socket mServerSocket = new Socket();

    @Override
    public void run() {
        mServerSocket.bind(Constants.sListenAddress, Constants.sListenPort);
        mServerSocket.listen();
        SelectModel select = new SelectModel();

        select.addReadFd(mServerSocket);
        int i = select.select(0);
        if (!interrupted()) {
            Socket client = select.getReadSetSocket();
            if (client != null) {
                select.addReadFd(client);
            }
        }
    }
}