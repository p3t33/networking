#ifndef _TCP_CLIENT_
#define _TCP_CLIENT_
/*******************************************************************************
*                             tcp client
*                       =====================
* File Name: tcp_client.hpp
* Related files: tcp_client.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 5.11.19
* Last update: 6.11.19
*******************************************************************************/


#include <arpa/inet.h> // sockaddr_in
#include <string> // std::string
#include <vector>
#include <fstream> // std::ofstream m_file



namespace med
{

class TCPClient
{

public:
    TCPClient(std::string port = "8080",
             std::string ip_address = "127.0.0.1",
             std::string file_name = "file");
    ~TCPClient();

    TCPClient(const TCPClient&) = delete;
    TCPClient& operator=(const TCPClient&) = delete;
    TCPClient(const TCPClient&&) = delete;
    TCPClient& operator=(const TCPClient&&) = delete;

    void communicate_with_server();

private:
    // auxiliary functions for the ctor
    void configure_socket(size_t port, std::string& ip_address);
    
    using socket_address_t  = struct sockaddr;
    void connect_to_server();

    std::ifstream m_file; // read_only from file
    int m_socket_file_descriptor;
    struct sockaddr_in m_server_address;
    std::string m_buffer;
};

} // namespace med
#endif //_TCP_CLIENT_
