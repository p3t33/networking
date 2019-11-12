#ifndef _UDP_CLIENT_
#define _UDP_CLIENT_
/*******************************************************************************
*                             udp client
*                       =====================
* File Name: udp_client.hpp
* Related files: udp_client.cpp udp_client_test.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 12.11.19
* Last update: 12.11.19

*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <arpa/inet.h> // sockaddr_in
#include <string> // std::string
#include <vector> // vector
#include <fstream> // std::ofstream m_file

/*============================================================================*/

namespace med
{

class UDPClient
{

public:
    UDPClient(std::string port = "8080",
             std::string ip_address = "127.0.0.1",
             std::string file_name = "file");
    ~UDPClient();

    UDPClient(const UDPClient&) = delete;
    UDPClient& operator=(const UDPClient&) = delete;
    UDPClient(const UDPClient&&) = delete;
    UDPClient& operator=(const UDPClient&&) = delete;

    // Interface / API
    // ------------------------------------------------------------------
    void communicate_with_server();

private:
    using socket_address_t  = struct sockaddr;

    // Auxilary ctor functions
    // ------------------------------------------------------------------
    void configure_socket(size_t port, std::string& ip_address);

    // managing variables 
    // ----------------------------
    std::ifstream m_file; // read_only from file
    int m_socket_file_descriptor;
    struct sockaddr_in m_server_address;
    std::string m_buffer;
};

} // namespace med
#endif //_UDP_CLIENT_
