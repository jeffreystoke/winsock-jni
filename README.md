# winsock-jni

JNI Wrapper for WinSock API

[中文](./README-CN.md)

## Purpose

Give a try for using Java to do something windows native, and learn windows IO model in depth.

(for course net-dev)

## Features

- Windows native socket
- Select IO Model
- WSAEventSelect Model
- Overlapped IO Model
- Completion Port

Note: WSAAsyncSelect is NOT supported, cause it requires WinMain as its entrance

## Usage

### JAR

Build, then import the generated Jar

### Maven

// TODO

### Gradle

// TODO

## Build

0. Get Visual Studio and Java 8 installed, configure `JAVA_HOME` environment variable
1. Modify `native/build.gradle`, change `libs->winsock->headers.srcDir` and other path variables to match your own case
2. run `cd library && ../gradlew fatJar`

Gradle will download essential packages and build, output is `library/build/libs/winsock-jni-{VERSION}.jar`

## Examples

// TODO

## Note

- support Windows Platform only
- support VisualCpp toolchain only

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