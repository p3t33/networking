#!/bin/bash

#compile source code
#####################
#client source
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g tcp_client.cpp client.cpp -o tcp_client.out
#server source
g++ -std=c++11 -pedantic-errors -Wall -Wextra -g tcp_server.cpp server.cpp -o tcp_server.out

#open seconed terminal to run tcp_client.out
############################################
gnome-terminal --working-directory=${PWD} -- bash -c "./tcp_server.out ;exec bash"
#gnome-terminal --working-directory=${PWD} -- bash -c "./tcp_client.out 9090  ;exec bash"

# wait for server to finish setup
#################################
sleep 5

#run client 1
#############
./tcp_client.out 9090 127.0.0.1 ./client_text_files/text1.txt


