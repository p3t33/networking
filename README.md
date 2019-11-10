# Networking
This is an implementation of a client server communication over TCP and UDP.
client opens a file connects to a server and sends the content of the file to
the server. Server opens another file and writes the received information into
it. As of now server opens 3 ports, each with its own
thread and receives and  communicate with 3 clients simultaneously.

This is a beta version, final version will include UDP connectivity.

### Next on the Todo list
- [x] <del> Integrate an epoll </del>
- [x] <del> Integrate multi threaded communication execution in server</del>
- [X] <del> Integrate multiple sockets in server.</del> 
- [ ] implement UDP client.
- [ ] implement UDO communication on the server. 


### Getting Started
clone the project by typing in the command line:
```
git clone https://github.com/p3t33/networking.git
```

### Compiling and running the server and clients
In order to compile source code to binary and run the 3 clients and server: 
```
./compile_and_run.sh
```
to compile ony:
```
./compile.sh
```
unit testing for data_proxy.cpp is available at ./unit_test

After server and client ended communication data sent to server can be found
at ./server_output.txt

### Compilers and operating systems
* Development was done on ubuntu 18.04 LTS OS.
* Source code was compiled with GNU g++ (v7.4), std=11.
* Tested for memory leaks using Valgrind v3.13.0

### Authors

**Kobi Medrish** - *beta version* - [p3t33](https://github.com/p3t33)

### License

Licensed under the [GPLv3](http://www.gnu.org/licenses/gpl-3.0.html) license.