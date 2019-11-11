#!/bin/bash

# delete old server_output.txt #
################################
rm server_output.txt

# compile source code #
######################

./compile.sh

# open seconed terminal to run tcp_client.out #
###############################################
gnome-terminal --working-directory=${PWD} -- bash -c "./server.out ;exec bash"
#gnome-terminal --working-directory=${PWD} -- bash -c "./tcp_client.out 9090  ;exec bash"

# wait for server to finish setup #
###################################
sleep 5

# run client 1 #
################
gnome-terminal --working-directory=${PWD} -- bash -c "./client.out 9090 127.0.0.1 ./client_text_files/text1.txt ;exec bash"
gnome-terminal --working-directory=${PWD} -- bash -c "./client.out 9091 127.0.0.1 ./client_text_files/text2.txt ;exec bash"
gnome-terminal --working-directory=${PWD} -- bash -c "./client.out 9092 127.0.0.1 ./client_text_files/text3.txt ;exec bash"

#./tcp_client.out 9090 127.0.0.1 ./client_text_files/text1.txt
