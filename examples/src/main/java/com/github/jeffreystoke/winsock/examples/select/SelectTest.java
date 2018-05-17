package com.github.jeffreystoke.winsock.examples.select;

import com.github.jeffreystoke.winsock.examples.simple.SimpleClient;

public class SelectTest {
    public static void main(String[] args) throws InterruptedException {
        Thread selectServerT = new Thread(new SelectServer());

        selectServerT.start();
        Thread.sleep(1000);
        for (int i = 0; i < 10; i++) {
            new Thread(new SimpleClient()).start();
        }
        selectServerT.interrupt();

    }
}
