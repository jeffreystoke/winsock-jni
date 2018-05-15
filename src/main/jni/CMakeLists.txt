cmake_minimum_required(VERSION 3.10)
project(winsock_jni)

set(CMAKE_CXX_STANDARD 11)

find_package(JNI)

include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH}/win32)

add_library(libwinscok_jni SHARED winsock_jni.cpp winsock_jni.h)