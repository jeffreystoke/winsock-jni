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

package com.github.jeffreystoke.winsock.examples.event;

import com.github.jeffreystoke.winsock.examples.Constants;
import com.github.jeffreystoke.winsock.examples.Server;
import com.github.jeffreystoke.winsock.io.constant.NetEvent;
import com.github.jeffreystoke.winsock.io.model.EventSelectModel;
import com.github.jeffreystoke.winsock.io.struct.Socket;
import com.github.jeffreystoke.winsock.io.struct.WSAEvent;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import static com.github.jeffreystoke.winsock.io.constant.NetEvent.*;

public class EventSelectServer extends Server {

    List<WSAEvent> events = new ArrayList<>();

    @Override
    protected String getTag() {
        return EventSelectServer.class.getSimpleName();
    }

    @Override
    public void run() {
        mServerSocket = new Socket();
        mServerSocket.bind(Constants.sListenAddress, Constants.sListenPort);
        mServerSocket.listen();

        WSAEvent event = new WSAEvent(mServerSocket);
        events.add(event);

        EventSelectModel esm = new EventSelectModel();
        esm.bind(event, FD_ACCEPT, FD_CLOSE);
        while (true) {
            WSAEvent eve = esm.waitForMultipleEvents(events, 0);
            if (eve == null) {
                continue;
            }
            eve = esm.waitForMultipleEvents(Collections.singletonList(eve), 0);


            NetEvent ne;
            try {
                ne = eve.getNetEvent();
            } catch (IOException e1) {
                println("" + e1.getMessage());
                continue;
            }

            if (ne == FD_ACCEPT) {
                Socket client;
                try {
                    println("accept");
                    client = mServerSocket.accept();
                    println("client connected");
                    WSAEvent ce = new WSAEvent(client);
                    esm.bind(ce, FD_READ, FD_CLOSE);
                    events.add(ce);
                    println("client added to event list");
                    client.send(Constants.sMessage.getBytes());
                    println("sent message");
                } catch (IOException e) {
                    println("accept error " + e.getMessage());
                }
            }

            Socket client = eve.getSocket();
            if (ne == FD_READ) {
                try {
                    println("client message " + new String(client.recv()));
                } catch (IOException e) {
                    println("recv error " + e.getMessage());
                }
            } else if (ne == FD_CLOSE) {
                try {
                    println("close socket");
                    client.close();
                    println("closed socket");
                } catch (IOException e) {
                    println("close error " + e.getMessage());
                }
            }
        }
    }
}