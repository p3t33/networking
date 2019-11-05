/*******************************************************************************
*                           tcp client
*                       =====================
* File Name: tcp_client.cpp
* Related files: tcp_client.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 5.11.19
* Last update: 5.11.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <string.h> // bzero
#include <unistd.h>  // write
#include <iostream> // std::cout

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/tcp_client.hpp"

/*============================================================================*/
/*                                                           global variables */
/*                                                           ~~~~~~~~~~~~~~~~ */
static const int failed_to_create_socket = -1;
static const int connected_successfully = 0;
static const size_t indefinitely = 1;

/*============================================================================*/
namespace hrd9
{
    
/*============================================================================*/
/*                                Class TCPClient                             */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
TCPClient::TCPClient(std::string port,
                     std::string ip_address,
                     std::string file_name):
                                                m_file(),
                                                m_socket_file_descriptor(0),
                                                m_server_address({}),
                                                m_buffer("")
{
    std::cout << "=================== Client ====================" << std::endl;

    m_file.open(file_name, std::ios::binary);
    std::string::size_type sizet;   // alias of size_t
    configure_socket(std::stoi (port ,&sizet), ip_address);
    connect_to_server();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
TCPClient::~TCPClient()
{
    close(m_socket_file_descriptor);
    m_file.close();
}

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */
/*                                                    communicate_with_server */
/*                                                    ~~~~~~~~~~~~~~~~~~~~~~~ */
void TCPClient::communicate_with_server()
{
    char buffer[80]; 
    std::string word;

    while (m_file >> word)
    {
        write(m_socket_file_descriptor, word.c_str(), word.size());

        sleep(1);

        read(m_socket_file_descriptor, buffer, sizeof(buffer));

        m_buffer.assign(buffer);

        std::cout << "Received from server: " << m_buffer.c_str();

        if ("exit\n" == m_buffer)
        {
            break;
        }
    }
}

/*============================================================================*/
/*                              Auxiliary functions                           */
/*============================================================================*/
/*                                                           configure_socket */
/*                                                           ~~~~~~~~~~~~~~~~ */
void TCPClient::configure_socket(size_t port, std::string& ip_address)
{
    // create socket
    m_socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0); 
    if (failed_to_create_socket == m_socket_file_descriptor)
    {
        throw std::runtime_error("socket creation");
    } 
  
    // assign address family, IP, PORT 
    m_server_address.sin_family = AF_INET; 
    m_server_address.sin_addr.s_addr = inet_addr(ip_address.c_str()); 
    m_server_address.sin_port = htons(port);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          connect_to_server */
/*                                                          ~~~~~~~~~~~~~~~~~ */
void TCPClient::connect_to_server()
{
    if (connected_successfully != connect(m_socket_file_descriptor,
                                          (socket_address_t*)&m_server_address,
                                           sizeof(m_server_address)))
    {
        throw std::runtime_error("connection with the server"); 
    }
}

} // namespace hrd9
