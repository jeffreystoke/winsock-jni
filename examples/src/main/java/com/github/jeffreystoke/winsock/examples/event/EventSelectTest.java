package com.github.jeffreystoke.winsock.examples.event;

import com.github.jeffreystoke.winsock.examples.simple.SimpleClient;
import com.github.jeffreystoke.winsock.examples.simple.SimpleServer;

public class EventSelectTest {
    public static void main(String[] args) throws InterruptedException {
        EventSelectServer serverT = new EventSelectServer();

        serverT.start();
        Thread.sleep(1000);
        for (int i = 0; i < 10; i++) {
            new SimpleClient().start();
        }
        Thread.sleep(1000);
        serverT.interrupt();
    }
}
