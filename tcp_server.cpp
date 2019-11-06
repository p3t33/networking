/*******************************************************************************
*                           tcp server
*                       =====================
* File Name: tcp_server.cpp
* Related files: tcp_server.hpp
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
#include <string.h> // bzero
#include <unistd.h>  // write
#include <iostream> // std::cout
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/tcp_server.hpp"
/*============================================================================*/
/*                                                           global variables */
/*                                                           ~~~~~~~~~~~~~~~~ */
static const int failed_to_create_socket = -1;
static const int socket_bind_successfully = 0;
static const int ready_to_accept_connections = 0;
static const int indefinitely = 1;
static const int accept_unsuccessfully = -1;

/*============================================================================*/
namespace med
{

/*============================================================================*/
/*                                Class TCPServer                             */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
TCPServer::TCPServer():
                                      m_file_data(0),
                                      m_incoming_port_number{9090, 9091, 9092},
                                      m_socket{{}},
                                      m_address({}),
                                      m_buffer(""),
                                      m_raw_data("server_output.txt")
{
    std::cout << "=================== Server ====================" << std::endl;

    configure_socket();
    wait_for_client(); 
}
                                                         
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
TCPServer::~TCPServer()
{
    close(m_socket[SOCKET_FD]);
    std::cout << "======================== dtor =================" << std::endl;
    m_raw_data.write_to_file(); 

    m_epoll.~EPollWrapper(); // close epoll file descriptor 
}

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */
/*                                                    communicate_with_client */
/*                                                    ~~~~~~~~~~~~~~~~~~~~~~~ */
void TCPServer::communicate_with_client()
{
    std::string word;

    while(0 != m_buffer.compare("_end_of_file_"))
    {
        int ready_file_descreptors = m_epoll.wait();

        for (int i = 0; i < ready_file_descreptors; ++i)
        {
            if (m_epoll[i].data.fd == m_socket[LISTEN_FD])
            {
                m_buffer.clear();

                char buffer[80]; 
                bzero(buffer, sizeof(buffer)); 
        
                // read the message from client and copy it in buffer 
                read(m_socket[LISTEN_FD], buffer, sizeof(buffer)); 

                m_buffer.assign(buffer);
                m_raw_data.gate_way(m_buffer.c_str());
            
                // m_file.write(m_buffer.c_str(), m_buffer.length());
            
                std::cout << "Received from client: "
                          << m_buffer.c_str() << std::endl;

                // save incoming word from server
                m_file_data.push_back(m_buffer.c_str());

                bzero(buffer, sizeof(buffer));

                // and send that buffer to client 
                write(m_socket[LISTEN_FD], "All good\n", 10); 
            } 
        }    
    }    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                            write_to_logger */
/*                                                            ~~~~~~~~~~~~~~~ */

/*============================================================================*/
/*                               Auxiliary functions                          */
/*============================================================================*/
/*                                                           configure_socket */
/*                                                           ~~~~~~~~~~~~~~~~ */
void TCPServer::configure_socket()
{
    m_socket[SOCKET_FD] = socket(AF_INET, SOCK_STREAM, 0); 
    if (failed_to_create_socket == m_socket[SOCKET_FD])
    {
        throw std::runtime_error("socket creation");
    } 

    // assign IP, PORT 
    m_address[SERVER].sin_family = AF_INET; 
    m_address[SERVER].sin_addr.s_addr = htonl(INADDR_ANY); 
    m_address[SERVER].sin_port = htons(m_incoming_port_number[0]); 
  
    // Binding newly created socket to given IP
    if (socket_bind_successfully != (bind(m_socket[SOCKET_FD],
                                          (socket_address_t*)&m_address[SERVER],
                                           sizeof(m_address[SERVER]))))
    {
        throw std::runtime_error("socket bind"); 
    } 
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                            wait_for_client */
/*                                                            ~~~~~~~~~~~~~~~ */
void TCPServer::wait_for_client()
{
    // Now server is ready to listen
    if (ready_to_accept_connections != listen(m_socket[SOCKET_FD], 0))
    {
        throw std::runtime_error("Listen"); 
    }

    socklen_t address_length = sizeof(m_address[CLIENT]); 
  
    // Accept the data packet from client
    m_socket[LISTEN_FD] = accept(m_socket[SOCKET_FD],
                                        (socket_address_t*)&m_address[CLIENT],
                                        &address_length);
                                        
    if (accept_unsuccessfully == m_socket[LISTEN_FD])
    {
        throw std::runtime_error("server acccept");
    }

    m_epoll.add(m_socket[LISTEN_FD]);
}

} // namespace med
