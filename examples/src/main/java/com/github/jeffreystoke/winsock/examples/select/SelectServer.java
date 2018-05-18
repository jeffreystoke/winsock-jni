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

package com.github.jeffreystoke.winsock.examples.select;

import com.github.jeffreystoke.winsock.examples.Constants;
import com.github.jeffreystoke.winsock.examples.Server;
import com.github.jeffreystoke.winsock.io.model.SelectModel;
import com.github.jeffreystoke.winsock.io.struct.Socket;

import java.io.IOException;

public class SelectServer extends Server {

    @Override
    protected String getTag() {
        return SelectServer.class.getSimpleName();
    }

    @Override
    public void run() {
        mServerSocket.bind(Constants.sListenAddress, Constants.sListenPort);
        mServerSocket.listen();

        SelectModel sm = new SelectModel();
        sm.addReadSocket(mServerSocket);
        while (true) {
            if (sm.run(0) < 1) {
                println("select failed");
                break;
            }

            Socket s = sm.getReadSetSocket();
            if (s == null) {
                continue;
            }

            if (s.equals(mServerSocket)) {
                try {
                    println("accept");
                    Socket client = mServerSocket.accept();
                    println("client connected");
                    sm.addReadSocket(client);
                    println("client added to read fd set");
                    client.send(Constants.sMessage.getBytes());
                    println("sent message");
                } catch (IOException e) {
                    println("accept error", e.getMessage());
                }
            } else {
                try {
                    println("client message", new String(s.recv()));
                } catch (IOException e) {
                    println("recv error ", e.getMessage());
                    try {
                        s.close();
                    } catch (IOException e1) {
                        println("close error ", e1.getMessage());
                    }
                }
            }
        }
    }
}