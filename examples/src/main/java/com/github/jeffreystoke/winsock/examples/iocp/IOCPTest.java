package com.github.jeffreystoke.winsock.examples.iocp;

import com.github.jeffreystoke.winsock.examples.simple.SimpleClient;

public class IOCPTest {
    public static void main(String[] args) throws InterruptedException {
        IOCPServer serverT = new IOCPServer();

        serverT.start();
        Thread.sleep(1000);
        for (int i = 0; i < 50; i++) {
            new SimpleClient().start();
        }
        Thread.sleep(5000);
        serverT.interrupt();
    }
}
