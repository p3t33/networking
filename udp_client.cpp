/*******************************************************************************
*                           udp client
*                       =====================
* File Name: udp_client.cpp
* Related files: udp_client.hpp udp_client_test.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 12.11.19
* Last update: 24.11.19
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
#include "./include/udp_client.hpp"

/*============================================================================*/
/*                                                           global variables */
/*                                                           ~~~~~~~~~~~~~~~~ */
static const int failed_to_create_socket = -1;

/*============================================================================*/
namespace med
{
    
/*============================================================================*/
/*                                Class UDPClient                             */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
UDPClient::UDPClient(std::string port, std::string file_name):
                                                    m_file(),
                                                    m_socket_file_descriptor(0),
                                                    m_server_address({}),
                                                    m_buffer("")
{
    std::cout << "=================== Client ====================" << std::endl;

    m_file.open(file_name, std::ios::binary);
    std::string::size_type sizet;   // alias of size_t
    configure_socket(std::stoi (port ,&sizet));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
UDPClient::~UDPClient()
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
void UDPClient::communicate_with_server()
{
    char buffer[buffer_size] = {0};
    std::string word;
    char const *message = "ping"; 
    socklen_t address_length = sizeof(m_server_address);

    for (size_t i = 0; i < 5; ++ i)
    {
        sleep(1);
        sendto(m_socket_file_descriptor,
               reinterpret_cast<const char *>(message),
               strlen(message), 
               MSG_CONFIRM,
               reinterpret_cast<sockaddr*> (&m_server_address),
               sizeof(m_server_address));  
                                
        recvfrom(m_socket_file_descriptor,
                 static_cast<char*>(buffer),
                 buffer_size,  
                 MSG_WAITALL,
                 reinterpret_cast<sockaddr*> (&m_server_address), 
                 &address_length); 

        word.assign(buffer);
        std::cout << "Received from server: " << word << std::endl;
    }        
}

/*============================================================================*/
/*                              Auxiliary functions                           */
/*============================================================================*/
/*                                                           configure_socket */
/*                                                           ~~~~~~~~~~~~~~~~ */
void UDPClient::configure_socket(size_t port)
{
    m_socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0); 
    if (failed_to_create_socket == m_socket_file_descriptor)
    {
        throw std::runtime_error("socket creation");
    } 
  
    // assign address family, IP, PORT 
    m_server_address.sin_family = AF_INET; 
    m_server_address.sin_addr.s_addr = INADDR_ANY; 
    m_server_address.sin_port = htons(port); // comunication port
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          connect_to_server */
/*                                                          ~~~~~~~~~~~~~~~~~ */

} // namespace med
