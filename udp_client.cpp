/*******************************************************************************
*                           udp client
*                       =====================
* File Name: udp_client.cpp
* Related files: udp_client.hpp udp_client_test.cpp
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
static const int connected_successfully = 0;

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
UDPClient::UDPClient(std::string port,
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
    char buffer[80] = {0};
    std::string word;
    char const *message = "ping"; 
    socklen_t address_length = sizeof(m_server_address);

    for (size_t i = 0; i < 5; ++ i)
    {
        sleep(1);
        sendto(m_socket_file_descriptor, (const char *)message, strlen(message), 
        MSG_CONFIRM, (const struct sockaddr *) &m_server_address, sizeof(m_server_address));  
                                
        ssize_t number_of_read_bytes = recvfrom(m_socket_file_descriptor,
                                                (char *)buffer,
                                                sizeof(buffer),  
                                                MSG_WAITALL,
                                                (struct sockaddr *) &m_server_address, 
                                                &address_length); 
        buffer[number_of_read_bytes] = '\0'; 
        printf("Server : %s\n", buffer); 
  
    }    
   // write(m_socket_file_descriptor, "_end_of_file_" ,13);
}

/*============================================================================*/
/*                              Auxiliary functions                           */
/*============================================================================*/
/*                                                           configure_socket */
/*                                                           ~~~~~~~~~~~~~~~~ */
void UDPClient::configure_socket(size_t port, std::string& ip_address)
{
    // TODO: socket(AF_INET, SOCK_DGRAM, 0)) < 0
    // create socket
    m_socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0); 
    if (failed_to_create_socket == m_socket_file_descriptor)
    {
        throw std::runtime_error("socket creation");
    } 
  
    // assign address family, IP, PORT 
    m_server_address.sin_family = AF_INET; 
    m_server_address.sin_addr.s_addr = INADDR_ANY; 
    m_server_address.sin_port = htons(8080); // comunication port
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          connect_to_server */
/*                                                          ~~~~~~~~~~~~~~~~~ */

} // namespace med
