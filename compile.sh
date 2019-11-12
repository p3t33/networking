#!/bin/bash

# ompile source code #
######################

#tcp client source
clang++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o tcp_client_test.out \
tcp_client.cpp \
tcp_client_test.cpp 

#udp client source
clang++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o udp_client_test.out \
udp_client.cpp \
udp_client_test.cpp

#server source
clang++ -std=c++11 -pedantic-errors -Wall -Wextra -g -pthread -o server.out \
tcp_udp_server.cpp \
data_proxy.cpp \
server.cpp \
epoll_wrapper.cpp
