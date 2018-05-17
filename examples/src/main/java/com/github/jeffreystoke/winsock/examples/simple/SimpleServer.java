package com.github.jeffreystoke.winsock.examples.simple;

import com.github.jeffreystoke.winsock.examples.Constants;
import com.github.jeffreystoke.winsock.io.struct.Socket;

import java.io.IOException;

public class SimpleServer implements Runnable {
    private Socket mServerSocket = new Socket();

    @Override
    public void run() {
        try {
            mServerSocket.bind(Constants.sListenAddress, Constants.sListenPort);
            mServerSocket.listen();
            Socket client = mServerSocket.accept();
            System.out.println("CLIENT MESSAGE: " + new String(client.recv()));
            client.send(Constants.sMessage.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}