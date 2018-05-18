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
import com.github.jeffreystoke.winsock.io.struct.*;
import org.jetbrains.annotations.NotNull;

import java.io.IOException;

public class IOCPServer extends WSAServer {

    private CompletionPortModel.Callback mCallback = new CompletionPortModel.Callback() {
        @Override
        public void onRecv(@NotNull Socket socket, @NotNull byte[] data) {
            println("client message", new String(data));
        }

        @Override
        public void onSend(@NotNull Socket socket) {
            println("socket send", socket.getAddress());
        }

        @Override
        public void onClose(@NotNull Socket socket) {
            try {
                socket.close();
                socket.destroy();
            } catch (IOException e) {
                println("close error", e.getMessage());
            }
        }

        @Override
        public void onError(@NotNull Socket socket) {
            println("socket error", socket.getAddress());
        }
    };

    @Override
    protected String getTag() {
        return IOCPServer.class.getSimpleName();
    }

    @Override
    public void run() {
        CompletionKey ck = new CompletionKey(mServerSocket);
        CompletionPortModel cpm = new CompletionPortModel();
        cpm.createServerThreads();
        cpm.setCallback(mCallback);
        mServerSocket.bind(Constants.sListenAddress, Constants.sListenPort);
        mServerSocket.listen();

        while (true) {
            try {
                WSASocket client = mServerSocket.accept();
                cpm.create(new CompletionKey(client));
                WSAEvent event = new WSAEvent(client);
                WSAOverlapped overlapped = new WSAOverlapped(event);
                client.wsaRecv(overlapped);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}