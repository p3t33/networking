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
#include <thread> //std::thread
/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/tcp_server.hpp"
/*============================================================================*/
/*                                                           global variables */
/*                                                           ~~~~~~~~~~~~~~~~ */
static const int failed_to_create_socket = -1;
static const int socket_bind_successfully = 0;
static const int ready_connections = 0;
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
                                      m_socket{chanels_num},
                                      m_address{chanels_num},
                                      m_thread{chanels_num},
                                      m_port{TCP1, TCP2, TCP3},
                                      m_file_data(0),
                                      m_buffer(""),
                                      m_raw_data("server_output.txt"),
                                      m_epoll(epoll_multithread_flag)
{
    std::cout << "=================== Server ====================" << std::endl;
    
    for (size_t i = 0; i < chanels_num; ++i)
    {
        m_thread[i] = std::thread(&TCPServer::execute_communication,
                                this,
                                m_socket[i],
                                m_port[i],
                                std::ref(m_address[i][0]));
    }
    
}
                                                         
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
TCPServer::~TCPServer()
{
    for (size_t i = 0; i < chanels_num; ++i)
    {

        m_thread[i].join();
        close((m_socket[i])[SOCKET_FD]);
    }

    std::cout << "======================== dtor =================" << std::endl;
    m_raw_data.write_to_file(); 
}

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */
/*                                                    communicate_with_client */
/*                                                    ~~~~~~~~~~~~~~~~~~~~~~~ */
void TCPServer::communicate_with_client(int* communication_socket)
{
    //struct epoll_event* mepoll_events = new epoll_event[10];
    
    epoll_event epoll_events[chanels_num];
    std::string word;

    while(0 != m_buffer.compare("_end_of_file_"))
    {
        int ready_file_descreptors = m_epoll.wait(epoll_events);

        for (int i = 0; i < ready_file_descreptors; ++i)
        {
            if (epoll_events[i].data.fd == communication_socket[LISTEN_FD])
            {
                m_buffer.clear();

                char buffer[80]; 
                bzero(buffer, sizeof(buffer)); 
        
                // read the message from client and copy it in buffer 
                read(communication_socket[LISTEN_FD], buffer, sizeof(buffer)); 

                m_buffer.assign(buffer);
                m_raw_data.gate_way(m_buffer.c_str());
            
                // m_file.write(m_buffer.c_str(), m_buffer.length());
            
                std::cout << "Received from client: "
                          << m_buffer.c_str() << std::endl;

                // save incoming word from server
                m_file_data.push_back(m_buffer.c_str());

                bzero(buffer, sizeof(buffer));

                // and send that buffer to client 
                write(communication_socket[LISTEN_FD], "All good\n", 10); 
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
void TCPServer::configure_socket(int port_number,
                                 int* communication_socket,
                                 sockaddr_in* address)
{
    communication_socket[SOCKET_FD] = socket(AF_INET, SOCK_STREAM, 0); 
    if (failed_to_create_socket == communication_socket[SOCKET_FD])
    {
        throw std::runtime_error("socket creation");
    } 

    // assign IP, PORT 
    address[SERVER].sin_family = AF_INET; 
    address[SERVER].sin_addr.s_addr = htonl(INADDR_ANY); 
    address[SERVER].sin_port = htons(port_number); 
  
    // Binding newly created socket to given IP
    if (socket_bind_successfully != (bind(communication_socket[SOCKET_FD],
                                          (socket_address_t*)&address[SERVER],
                                           sizeof(address[SERVER]))))
    {
        throw std::runtime_error("socket bind"); 
    } 
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                            wait_for_client */
/*                                                            ~~~~~~~~~~~~~~~ */
void TCPServer::wait_for_client(int* communication_socket,
                                sockaddr_in* address)
{
    // Now server is ready to listen
    if (ready_connections != listen(communication_socket[SOCKET_FD], 0))
    {
        throw std::runtime_error("Listen"); 
    }

    socklen_t address_length = sizeof(address[CLIENT]); 
  
    // Accept the data packet from client
    communication_socket[LISTEN_FD] = accept(communication_socket[SOCKET_FD],
                                        (socket_address_t*)&address[CLIENT],
                                        &address_length);
                                        
    if (accept_unsuccessfully == communication_socket[LISTEN_FD])
    {
        throw std::runtime_error("server acccept");
    }

    m_epoll.add(communication_socket[LISTEN_FD]);

    communicate_with_client(communication_socket);
}

void TCPServer::execute_communication(int* communication_socket,
                                      int port_number,
                                      struct sockaddr_in& address)
{
    configure_socket(port_number, communication_socket, &address);
    wait_for_client(communication_socket, &address);
}

} // namespace med
