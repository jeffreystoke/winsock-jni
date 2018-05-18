package com.github.jeffreystoke.winsock.examples.overlapped;

import com.github.jeffreystoke.winsock.examples.simple.SimpleClient;

public class OverlappedTest {
    public static void main(String[] args) throws InterruptedException {
        OverlappedServer serverT = new OverlappedServer();

        serverT.start();
        Thread.sleep(1000);
        for (int i = 0; i < 10; i++) {
            new SimpleClient().start();
        }
        Thread.sleep(1000);
        serverT.interrupt();
    }
}
