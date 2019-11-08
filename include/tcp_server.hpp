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
* Last update: 6.11.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <vector> // m_file_data
#include <arpa/inet.h> // sockaddr_in
#include <string> // std::string
#include <fstream> // std::ofstream m_file
#include <thread> // std::thread

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */

#include "data_proxy.hpp"
#include "epoll_wrapper.hpp"
/*============================================================================*/


namespace med
{

class TCPServer
{

private:
    using socket_address_t  = struct sockaddr;
    enum Address {SERVER, CLIENT};
    enum Descriptor {SOCKET_FD, LISTEN_FD}; 

public:
    TCPServer();
    ~TCPServer();

    TCPServer(const TCPServer&) = delete;
    TCPServer& operator=(TCPServer&) = delete;
    TCPServer(const TCPServer&&) = delete;
    TCPServer& operator=(TCPServer&&) = delete;

    // Interface / API
    // ----------------------------------------------------------------

    // ------------------------------------------------------------------

private:
    // Auxilary ctor functions
    // ------------------------------------------------------------------
    void configure_socket();
    void wait_for_client();
    void communicate_with_client();
    void execute_communication();
    // ------------------------------------------------------------------

    std::vector<std::string> m_file_data;
    size_t m_incoming_port_number[3];
    int m_socket[2];
    struct sockaddr_in m_address[2];
    std::string m_buffer;

    DataProxy m_raw_data;
    EPollWrapper m_epoll;
    std::vector<std::thread> m_thread;
};

} // namespace med
#endif // _TCP_SERVER_
