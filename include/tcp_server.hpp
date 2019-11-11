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
* Last update: 11.11.19
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
#include <memory> // std::shared_ptr

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
    enum address {SERVER, CLIENT};
    enum file_descriptor {SOCKET_FD, LISTEN_FD};
    enum incoming_port {TCP1 = 9090, TCP2 = 9091, TCP3 = 9092, UDP1 = 8080}; 

    // chanels_num  is the number of communication chanels which is derived from 
    // number of incoming ports, it will define the number of m_thread, m_socket
    // and m_address
    static const int tcp_chanels_num = 3; // 3 tcp sockets and 1 udp socket
    static const int udp_chanels_num = 1;
    static const int total_chanles = tcp_chanels_num + udp_chanels_num;
    static const bool epoll_multithread_flag = true;
    class ThreadData; // auxiliary class used to pass data in a threadsafe
                      // manner to the thread function

public:
    TCPServer();
    ~TCPServer();

    TCPServer(const TCPServer&) = delete;
    TCPServer& operator=(TCPServer&) = delete;
    TCPServer(const TCPServer&&) = delete;
    TCPServer& operator=(TCPServer&&) = delete;

private:
    // Auxilary ctor functions
    // ------------------------------------------------------------------
    void configure_socket(std::shared_ptr<ThreadData> data);
    void wait_for_client(std::shared_ptr<ThreadData> data);
    void communicate_with_tcp_client(std::shared_ptr<ThreadData> data);
    void communicate_with_udp_client(std::shared_ptr<ThreadData> data);
    void execute_tcp_communication(std::shared_ptr<ThreadData> data);
    void execute_udp_communication(std::shared_ptr<ThreadData> data);

    // Managing variables 
    // ------------------------------------------------------------------
    // TCP socket pair, second socket initialized during accept function call
    std::vector<int[2]> m_socket;
    std::vector<sockaddr_in[2]> m_address; 
    std::vector<std::thread> m_thread; // each thread handles different socket
    std::vector<int> m_port;

    DataProxy m_raw_data; // handles incoming data from client/
    EPollWrapper m_epoll; // server epoll
    std::vector<std::shared_ptr<ThreadData>> m_thread_data;                                            
};

                             
} // namespace med
#endif // _TCP_SERVER_
