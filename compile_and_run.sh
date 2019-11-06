#!/bin/bash

# ompile source code #
######################

#client source
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o tcp_client.out \
tcp_client.cpp \
client.cpp 
#server source
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g -o tcp_server.out \
tcp_server.cpp \
data_proxy.cpp \
server.cpp

# open seconed terminal to run tcp_client.out #
###############################################
gnome-terminal --working-directory=${PWD} -- bash -c "./tcp_server.out ;exec bash"
#gnome-terminal --working-directory=${PWD} -- bash -c "./tcp_client.out 9090  ;exec bash"

# wait for server to finish setup #
###################################
sleep 5

# run client 1 #
################
./tcp_client.out 9090 127.0.0.1 ./client_text_files/text1.txt


