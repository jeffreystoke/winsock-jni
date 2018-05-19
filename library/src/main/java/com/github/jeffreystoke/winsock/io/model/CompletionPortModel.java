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

package com.github.jeffreystoke.winsock.io.model;

import com.github.jeffreystoke.winsock.io.internal.WinSock;
import com.github.jeffreystoke.winsock.io.struct.CompletionKey;
import com.github.jeffreystoke.winsock.io.struct.Socket;
import com.github.jeffreystoke.winsock.io.struct.Struct;
import com.github.jeffreystoke.winsock.io.struct.WSAOverlapped;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class CompletionPortModel extends Struct {

    private static Map<Long, CompletionPortModel> iocps = new HashMap<>();

    private static class Message {
        CompletionPortModel cpm;
        int opType;
        Socket socket;
        byte[] buffer;

        Message(CompletionPortModel cpm, int opType, Socket socket, byte[] buffer) {
            this.cpm = cpm;
            this.opType = opType;
            this.socket = socket;
            this.buffer = buffer;
        }
    }

    private static BlockingQueue<Message> messages = new LinkedBlockingQueue<>();
    private static Thread sMessageTaker = new Thread() {
        @Override
        public void run() {
            while (true) {
                if (interrupted()) {
                    return;
                }

                try {
                    Message msg = messages.take();
                    CompletionPortModel cp = msg.cpm;
                    Socket socket = msg.socket;
                    switch (msg.opType) {
                        case _op_read:
                            if (cp.mCallback != null) {
                                cp.mCallback.onRecv(socket, msg.buffer);
                            }
                        case _op_write:
                            if (cp.mCallback != null) {
                                cp.mCallback.onSent(socket);
                            }
                        case _op_close:
                            if (cp.mCallback != null) {
                                cp.mCallback.onClose(socket);
                            }
                        case _op_error:
                            if (cp.mCallback != null) {
                                cp.mCallback.onError(socket);
                            }
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    };


    private static final int _op_read = 0;
    private static final int _op_write = 1;
    private static final int _op_close = 2;
    private static final int _op_error = 3;

    private Callback mCallback;

    public interface Callback {
        void onRecv(Socket socket, byte[] data);

        void onSent(Socket socket);

        void onClose(Socket socket);

        void onError(Socket socket);
    }

    public static void onMessage(long cpPtr, long completionKeyPtr, int opType, byte[] buffer) {
        CompletionPortModel cp = iocps.getOrDefault(cpPtr, null);
        if (cp == null) {
            return;
        }
        CompletionKey cpk = CompletionKey.Companion.getCompletionKey(completionKeyPtr);
        if (cpk == null) {
            return;
        }
        cpk.getSocket().setAddress(cpk.getClientAddress());
        cpk.getSocket().setPort(cpk.getClientPort());
        messages.add(new Message(cp, opType, cpk.getSocket(), buffer));
    }

    public CompletionPortModel() {
        set_ptr(WinSock._create_iocp(0, 0, 0));

        if (get_ptr() == 0) {
            throw new RuntimeException("创建 IOCP 失败");
        }
        iocps.put(get_ptr(), this);

        if (!sMessageTaker.isAlive()) {
            sMessageTaker.start();
        }
    }

    public void create(CompletionKey completionKey) {
        WinSock._create_iocp(completionKey.getSocket().getPtr(), get_ptr(), completionKey.getPtr());
    }

    public void setCallback(Callback callback) {
        mCallback = callback;
    }


    public void createServerThreads() throws RuntimeException {
        createServerThreads(Runtime.getRuntime().availableProcessors() * 2);
    }

    public void createServerThreads(int count) throws RuntimeException {
        for (int i = 0; i < count; i++) {
            int ret = WinSock._create_server_thread(get_ptr());
            if (ret != 0) {
                throw new RuntimeException("创建线程 " + i + " 失败, 错误 " + ret);
            }
        }
    }

    public Boolean postQueuedCompletionStatus(int bytes, CompletionKey completionKey, WSAOverlapped overlapped) {
        return WinSock._post_queued_completion_status(get_ptr(), bytes, completionKey.getPtr(), overlapped.getPtr());
    }

    public void cancel(Socket socket) {
        WinSock._cancel_io(socket.getPtr());
    }
}
