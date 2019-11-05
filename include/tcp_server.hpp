#ifndef _TCP_SERVER_
#define _TCP_SERVER_

/*******************************************************************************
*                             tcp client
*                       =====================
* File Name: tcp_server.hpp
* Related files: tcp_server.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 5.11.19
* Last update: 5.11.19
*******************************************************************************/
#include <vector> // m_file_data
#include <arpa/inet.h> // sockaddr_in
#include <string> // std::string
#include <fstream> // std::ofstream m_file


namespace hrd9
{

class TCPServer
{
    enum Address {SERVER, CLIENT};
    enum Descriptor {SOCKET_FD, LISTEN_FD}; 

public:
    TCPServer(std::string server_file = "server_output.txt");
    ~TCPServer();

    TCPServer(const TCPServer&) = delete;
    TCPServer& operator=(TCPServer&) = delete;
    TCPServer(const TCPServer&&) = delete;
    TCPServer& operator=(TCPServer&&) = delete;

    void communicate_with_client();

private:

    // auxiliary
    using socket_address_t  = struct sockaddr;

    void configure_socket();
    void wait_for_client();

    std::vector<std::string> m_file_data;
    size_t m_incoming_port_number[3];
    int m_socket[2];
    struct sockaddr_in m_address[2];
    std::ofstream m_file; // write only
    std::string m_buffer;
};

} // namespace hrd9
#endif // _TCP_SERVER_
