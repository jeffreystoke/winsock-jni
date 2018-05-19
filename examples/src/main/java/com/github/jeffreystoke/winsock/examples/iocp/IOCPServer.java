/*
 * Copyright (c) 2018 JeffreyStoke (https://github.com/jeffreystoke)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.github.jeffreystoke.winsock.examples.iocp;


import com.github.jeffreystoke.winsock.examples.Constants;
import com.github.jeffreystoke.winsock.examples.WSAServer;
import com.github.jeffreystoke.winsock.io.model.CompletionPortModel;
import com.github.jeffreystoke.winsock.io.struct.CompletionKey;
import com.github.jeffreystoke.winsock.io.struct.Socket;
import com.github.jeffreystoke.winsock.io.struct.WSAEvent;
import com.github.jeffreystoke.winsock.io.struct.WSAOverlapped;
import com.github.jeffreystoke.winsock.io.util.UtilKt;
import org.jetbrains.annotations.NotNull;

import java.io.IOException;

public class IOCPServer extends WSAServer implements CompletionPortModel.Callback {

    @Override
    public void onRecv(@NotNull Socket socket, @NotNull byte[] data) {
        println("onRecv", new String(data));
    }

    @Override
    public void onSent(@NotNull Socket socket) {
        println("onSent");
    }

    @Override
    public void onClose(@NotNull Socket socket) {
        println("onClose");
    }

    @Override
    public void onError(@NotNull Socket socket) {
        println("onError");
    }

    @Override
    protected String getTag() {
        return IOCPServer.class.getSimpleName();
    }

    @Override
    public void run() {
        try {
            CompletionPortModel cpm = new CompletionPortModel();
            cpm.createServerThreads();
            cpm.setCallback(this);
            mServerSocket.bind(Constants.sListenAddress, Constants.sListenPort);
            mServerSocket.listen();

            while (true) {
                if (interrupted()) {
                    break;
                }
                try {
                    Socket client = mServerSocket.accept();
                    println("client connected");
                    cpm.create(new CompletionKey(client));
                    WSAEvent event = new WSAEvent(client);
                    WSAOverlapped overlapped = new WSAOverlapped(event);
                    client.postSend(Constants.sMessage.getBytes(), overlapped);
                    client.postRecv(overlapped);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        } finally {
            UtilKt.wsaCleanup();
        }

    }
}