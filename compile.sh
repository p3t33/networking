#!/bin/bash

# ompile source code #
######################

#client source
clang++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o tcp_client.out \
tcp_client.cpp \
client.cpp 
#server source
clang++ -std=c++11 -pedantic-errors -Wall -Wextra -g -pthread -o server.out \
tcp_udp_server.cpp \
data_proxy.cpp \
server.cpp \
epoll_wrapper.cpp
