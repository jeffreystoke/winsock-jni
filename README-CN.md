# winsock-jni

WinSock API 的 Java 封装 (使用 JNI)

[English](./README.md)

## 目的

尝试使用 Java 调用 Windows 平台 API, 深入学习 Windows IO 模型

相关课程: 网络应用于开发

## 特性

- Windows 原生 Socket
- Select模型
- WSAEventSelect 模型
- 重叠 IO 模型
- IOCP 模型

注: WSAAsyncSelect 由于需要 WinMain 入口无法支持

## 使用

1. 导入 Jar

## 构建

0. 安装好 Visual Studio 和 Java 8, 并配置好 `JAVA_HOME` 环境变量
1. 修改 `native/build.gradle`, 将 `libs->winsock->headers.srcDir` 及其他路径相关参数与本机匹配
2. 执行 `cd library && ../gradlew assemble`

Gradle 将会下载必要的依赖并开始构建, 输出结果 `build/libs/winsock-jni-{VERSION}.jar`

## 示例

// TODO

## 注意

- 仅支持 Windows 平台
- 仅支持 VisualCpp 编译工具链

## 开源许可

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