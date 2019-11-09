# Networking
This is an implementation of a client server communication over TCP.
client opens a file connects to a server and sends the content of the file to
the server. Server opens another file and writes the received information into
it. This is a beta version, as of now one client connects to the server, final
version will have 3 clients connecting simultaneously.

### Next on the Todo list
- [x] <del> Integrate an epoll </del>
- [x] <del> Integrate multi threaded communication execution in server</del>
- [X] <del>Integrate multiple sockets in server.</del> 
- [ ] add UDP communication. 

### Getting Started
clone the project by typing in the command line:
```
git clone https://github.com/p3t33/networking.git
```

### Compiling and running the server and client
1. Unit test is available for parser.cpp, navigate to ./unit_testing folder and
   run the following script(to compile a binary):
In order to compile source code to binary and run the client and server: 
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
code was compiled with GNU g++ using std=c++11. It was tested on ubuntu 18.04 LTS.
code was tested for memory leaks via valgrind 3.13.0

### Authors

**Kobi Medrish** - *beta version* - [p3t33](https://github.com/p3t33)

### License

Licensed under the [GPLv3](http://www.gnu.org/licenses/gpl-3.0.html) license.