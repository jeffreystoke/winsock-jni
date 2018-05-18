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

import com.github.jeffreystoke.winsock.examples.Server;
import com.github.jeffreystoke.winsock.io.model.OverlappedModel;
import com.github.jeffreystoke.winsock.io.struct.WSAEvent;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class OverlappedServer extends Server {

    List<WSAEvent> events = new ArrayList<>();

    @Override
    protected String getTag() {
        return OverlappedServer.class.getSimpleName();
    }

    @Override
    public void run() {
        super.run();
        WSAEvent event = new WSAEvent(mServerSocket);
        events.add(event);

        OverlappedModel om = new OverlappedModel();
        while (true) {
            WSAEvent eve = om.waitForMultipleEvents(events, 0);
            eve = om.waitForMultipleEvents(Collections.singletonList(eve), 0);
        }
    }
}