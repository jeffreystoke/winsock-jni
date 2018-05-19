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

package com.github.jeffreystoke.winsock.examples.overlapped;

import com.github.jeffreystoke.winsock.examples.Constants;
import com.github.jeffreystoke.winsock.examples.Server;
import com.github.jeffreystoke.winsock.io.model.OverlappedModel;
import com.github.jeffreystoke.winsock.io.struct.Socket;
import com.github.jeffreystoke.winsock.io.struct.WSAEvent;
import com.github.jeffreystoke.winsock.io.struct.WSASocket;

import java.io.IOException;
import java.util.Vector;

public class OverlappedServer extends Server {

    private Vector<WSAEvent> mEvents = new Vector<>();
    private OverlappedModel om = new OverlappedModel();

    private Thread mIOHandler = new Thread(() -> {
        while (true) {
            if (interrupted()) {
                break;
            }

            WSAEvent eve = null;

            try {
                eve = om.waitForMultipleEvents(mEvents, 0);
            } catch (RuntimeException e) {

            }

            if (eve != null) {
                eve.reset();
            }

            om.getOverlappedResult(eve.getSocket(),
                    eve.getRelatedReadOverlappedHandles().lastElement(), false, 0);

        }
    });

    @Override
    protected String getTag() {
        return OverlappedServer.class.getSimpleName();
    }

    @Override
    public void run() {
        mServerSocket = new WSASocket();
        mServerSocket.bind(Constants.sListenAddress, Constants.sListenPort);
        mServerSocket.listen();

        while (true) {
            if (interrupted()) {
                break;
            }

            try {
                Socket s = mServerSocket.accept();
                mEvents.add(new WSAEvent(s));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}