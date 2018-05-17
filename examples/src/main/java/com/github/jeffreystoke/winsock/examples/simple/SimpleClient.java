package com.github.jeffreystoke.winsock.examples.simple;

import com.github.jeffreystoke.winsock.examples.Constants;
import com.github.jeffreystoke.winsock.io.struct.Socket;

import java.io.IOException;

public class SimpleClient implements Runnable {

    private Socket mSocket = new Socket();

    @Override
    public void run() {
        try {
            mSocket.connect(Constants.sListenAddress, Constants.sListenPort);
            mSocket.send(Constants.sMessage.getBytes(), 0);
            System.out.println("SERVER MESSAGE: " + new String(mSocket.recv()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}