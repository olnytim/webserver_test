cmake_minimum_required(VERSION 3.27)
project(webserver)

set(CMAKE_CXX_STANDARD 98)

add_executable(webserver srcs/main.cpp
        srcs/sockets/SocketListener.cpp
        srcs/sockets/WebServer.cpp
        srcs/utils/util.cpp)