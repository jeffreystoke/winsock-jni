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

package com.github.jeffreystoke.winsock.examples.simple;

import com.github.jeffreystoke.winsock.examples.Constants;
import com.github.jeffreystoke.winsock.examples.Server;
import com.github.jeffreystoke.winsock.io.struct.Socket;

import java.io.IOException;

public class SimpleServer extends Server {

    @Override
    protected String getTag() {
        return SimpleServer.class.getSimpleName();
    }

    @Override
    public void run() {
        super.run();

        try {
            Socket client = mServerSocket.accept();
            System.out.println("CLIENT MESSAGE: " + new String(client.recv()));
            client.send(Constants.sMessage.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}