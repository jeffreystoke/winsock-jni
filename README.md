# winsock-jni

JNI Wrapper for WinSock API (under heavy development)

## Purpose

Give a try for using Java to do something windows native, and learn windows IO model in depth.

(for course net-dev)

## Features

- Windows native socket (done)
- Select IO Model (done)
- WSAAsyncSelect Model (Not Supported)
- WSAEventSelect Model (done)
- Overlapped IO Model (in progress)
- Completion Port (in progress)

## Build

```bash
./gradlew jar
```

## Note

For Windows Platform only

## LICENSE

```text
Copyright JeffreyStoke (https://github.com/jeffreystoke)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```