#!/bin/bash

# ompile source code #
######################

#client source
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o tcp_client.out \
tcp_client.cpp \
client.cpp 
#server source
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -pthread -o tcp_server.out \
tcp_server.cpp \
data_proxy.cpp \
server.cpp \
epoll_wrapper.cpp
