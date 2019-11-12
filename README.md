# TCP / UDP server - client
This is an implementation of a client server communication over TCP and UDP.
TCP client opens a file, connects to the server and sends the content of the
file to it. Server opens another file and writes the received information into
it. UDP client sends a "ping" to the server and once server receives it, server
sends a "pong" to the client. Each socket handled by its own thread and server 
communicate with all of the clients simultaneously. The amount of sockets and
their communication type is configurable. 

As of now, server configured for 3 TCP ports and 1 UDP port communication.
This is a beta version.

### Next on the Todo list
- [x] <del> Integrate an epoll for server side TCP communication </del>
- [x] <del> Integrate multi threaded communication execution on server</del>
- [X] <del> Integrate multiple sockets on server.</del> 
- [X] <del> Implement UDP communication on the server.</del>
- [ ] implement UDP client.
 


### Getting Started
clone the project by typing in the command line:
```bash
git clone https://github.com/p3t33/networking.git
```

### Compiling and running the server and clients
In order to compile source code to binary and run the 3 clients and server: 
```sh
./compile_and_run.sh
```
to compile ony:
```sh
./compile.sh
```
unit testing for data_proxy.cpp is available at ./unit_test

After server and client ends communication data sent to server can be found
at ./server_output.txt

In case you decide to run manually (after ./compile.sh is done):
1. Run ./server.out which is preconfigured with tcp ports 9090, 9091, 9092.
2. Now run the 3 clients (clients must be run with environment variables):
```bash
./tcp_client.out 9090 127.0.0.1 ./client_text_files/text1.txt
./tcp_client.out 9091 127.0.0.1 ./client_text_files/text2.txt   
./tcp_client.out 9092 127.0.0.1 ./client_text_files/text3.txt
```     
### Compilers and operating systems
* Development was done on ubuntu 18.04 LTS OS.
* Source code was compiled with GNU g++ v7.4 and clang++ v6.0.0, std=11
* Tested for memory leaks using Valgrind v3.13.0

### Authors

**Kobi Medrish** - [p3t33](https://github.com/p3t33)

### License
Licensed under the [GPLv3](http://www.gnu.org/licenses/gpl-3.0.html) license.