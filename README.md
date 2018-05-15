# winsock-jni

JNI Wrapper for WinSock API (under heavy development)

[中文](./README-CN.md)

## Purpose

Give a try for using Java to do something windows native, and learn windows IO model in depth.

(for course net-dev)

## Features

- Windows native socket (done)
- Select IO Model (done)
- WSAEventSelect Model (done)
- Overlapped IO Model (in progress)
- Completion Port (in progress)

Note: WSAAsyncSelect is NOT supported, cause it requires WinMain as its entrance

## Usage

// TODO

## Build

0. Get Visual Studio installed
1. Modify `build.gradle`, change `libs->winsock->headers.srcDir` and other path to match your own system
2. run  `./gradlew assemble` within command line interface

Gradle will download essential packages and build, output dir is `build/libs`

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