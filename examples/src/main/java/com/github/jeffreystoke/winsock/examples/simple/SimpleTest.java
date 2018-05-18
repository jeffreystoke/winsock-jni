package com.github.jeffreystoke.winsock.examples.simple;

public class SimpleTest {

    public static void main(String[] args) throws InterruptedException {
        Thread serverT = new Thread(new SimpleServer());
        Thread clientT = new Thread(new SimpleClient());
        serverT.start();
        Thread.sleep(1000);
        clientT.start();
        Thread.sleep(1000);
    }
}
