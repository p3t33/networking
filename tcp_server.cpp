/*******************************************************************************
*                           tcp server
*                       =====================
* File Name: tcp_server.cpp
* Related files: tcp_server.hpp
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
static const int accept_unsuccessfully = -1;

/*============================================================================*/
namespace med
{

/*============================================================================*/
/*                             auxiliary Class ThreadData                     */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
class TCPServer::ThreadData
{
    public:
        ThreadData(int* communication_socket,
                   int port_number,
                   sockaddr_in* address,
                   int socket_type):
                   m_communication_socket(communication_socket),
                   m_port_number(port_number),
                   m_address(address),
                   m_socket_type(socket_type)
        {}
    
        int* m_communication_socket;
        int m_port_number;
        struct sockaddr_in* m_address;
        int m_socket_type;
};


/*============================================================================*/
/*                                Class TCPServer                             */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
TCPServer::TCPServer():
                                      m_socket{total_chanles},
                                      m_address{total_chanles},
                                      m_thread{total_chanles},
                                      m_port{TCP1, TCP2, TCP3, UDP1},
                                      m_raw_data("server_output.txt"),
                                      m_epoll(epoll_multithread_flag),
                                      m_thread_data{total_chanles}
                                   
{
    std::cout << "=================== Server ====================" << std::endl;
    

        /*
         * There were 3 options to pass arguments to thread function
         * 1. Pass single i to each thread and then using [] get access to 
         *    to relevent member in vector (for example m_socket[i]). 
         *    this option is not thread safe, all of the threads use the
         *    operator=[] to get access to the same thread.
         * 2. Pass all of the relevent data (m_socket, m_port,m_address) as
         *    arguments to the thread function. In this way operator[] is
         *    used only by the main thread. This should work but it requres
         *    to keep a pointer for each argument, pointer which is freed only
         *    when the server goes down and process finishes.
         * 3. Use a single struct to hold all of the arguments, this means only
         *    one pointer is used and in the future all changes are done inside
         *    the ThreadData struct.
         */
    for (size_t i = 0; i < tcp_chanels_num; ++i)
    {
        m_thread_data[i] = std::make_shared<ThreadData>(m_socket[i],
                                                        m_port[i],
                                                        m_address[i],
                                                        SOCK_STREAM);

         m_thread[i] = std::thread(&TCPServer::execute_tcp_communication,
                                   this,
                                   std::ref(m_thread_data[i])); 
    }

    for (size_t i = tcp_chanels_num; i < total_chanles; ++i)
    {
        m_thread_data[i] = std::make_shared<ThreadData>(m_socket[i],
                                                        m_port[i],
                                                        m_address[i],
                                                        SOCK_DGRAM);

        m_thread[i] = std::thread(&TCPServer::execute_udp_communication,
                                  this,
                                  std::ref(m_thread_data[i]));     
    }
}
                                                         
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
TCPServer::~TCPServer()
{
    for (size_t i = 0; i < (total_chanles); ++i)
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
/*                                                communicate_with_tcp_client */
/*                                                ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void TCPServer::communicate_with_tcp_client(std::shared_ptr<ThreadData> data)
{
    // epoll is thread safe, but each thread should have its own epoll_event
    // ready list array or else undefined behavior may occur due to race
    // conditions
    epoll_event epoll_events[tcp_chanels_num];
    std::string word;
    word.clear();

    while(0 != word.compare("_end_of_file_"))
    {
        int ready_file_descreptors = m_epoll.wait(epoll_events);

        for (int i = 0; i < ready_file_descreptors; ++i)
        {
            if (epoll_events[i].data.fd == 
                                        data->m_communication_socket[LISTEN_FD])
            {
                word.clear();

                char buffer[80]; 
                bzero(buffer, sizeof(buffer)); 
        
                // read the message from client and copy it in buffer 
                read(data->m_communication_socket[LISTEN_FD],
                     buffer, sizeof(buffer)); 

                word.assign(buffer);
                m_raw_data.gate_way(word.c_str());
            
                std::cout << "Received from client: "
                          << word.c_str() << std::endl;

                bzero(buffer, sizeof(buffer));

                // and send that buffer to client 
                write(data->m_communication_socket[LISTEN_FD],
                      "All good\n", 10); 
            } 
        }    
    }
    // communication is over and file descriptor is no longer needes to be
    //
    m_epoll.remove(data->m_communication_socket[LISTEN_FD]);
}

void TCPServer::communicate_with_udp_client(std::shared_ptr<ThreadData> data)
{
    char buffer[80];
  
    socklen_t address_length;
    char const *message = "pong";
    std::string word;
    sockaddr_in test;



    while (1)
    {
        sleep(1);
        int number_of_read_bytes; 
        number_of_read_bytes = recvfrom(data->m_communication_socket[SOCKET_FD],
                                        (char *)buffer,
                                        sizeof(buffer),  
                                        MSG_WAITALL,
                                        ( struct sockaddr *) &test, 
                                        &address_length); 
        std::cout << "passed recvfrom" << std::endl;

        buffer[number_of_read_bytes] = '\0'; 
        printf("Client : %s\n", buffer); 
        sendto(data->m_communication_socket[SOCKET_FD],
              (const char *)message,
              strlen(message),  
              MSG_CONFIRM,
              (const struct sockaddr *) &test, 
              address_length); 

        printf("Hello message sent.\n");  
    }  
}

/*============================================================================*/
/*                               Auxiliary functions                          */
/*============================================================================*/
/*                                                           configure_socket */
/*                                                           ~~~~~~~~~~~~~~~~ */
void TCPServer::configure_socket(std::shared_ptr<ThreadData> data)
{
    data->m_communication_socket[SOCKET_FD] = socket(AF_INET,
                                                     data->m_socket_type,
                                                     0); 
    if (failed_to_create_socket == data->m_communication_socket[SOCKET_FD])
    {
        throw std::runtime_error("socket creation");
    } 

    // assign IP, PORT 
    data->m_address[SERVER].sin_family = AF_INET; 
    data->m_address[SERVER].sin_addr.s_addr = htonl(INADDR_ANY); 
    data->m_address[SERVER].sin_port = htons(data->m_port_number); 

    // Binding newly created socket to given IP
    if (socket_bind_successfully != 
                                  (bind(data->m_communication_socket[SOCKET_FD],
                                  (socket_address_t*)&data->m_address[SERVER],
                                   sizeof(data->m_address[SERVER]))))
    {
        throw std::runtime_error("socket bind"); 
    } 
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                            wait_for_client */
/*                                                            ~~~~~~~~~~~~~~~ */
void TCPServer::wait_for_client(std::shared_ptr<ThreadData> data)
{
    // Now server is ready to listen
    if (ready_connections != listen(data->m_communication_socket[SOCKET_FD], 0))
    {
        throw std::runtime_error("Listen"); 
    }

    socklen_t address_length = sizeof(data->m_address[CLIENT]); 
  
    // Accept the data packet from client
    data->m_communication_socket[LISTEN_FD] =
                                 accept(data->m_communication_socket[SOCKET_FD],
                                 (socket_address_t*)&data->m_address[CLIENT],
                                 &address_length);
                                        
    if (accept_unsuccessfully == data->m_communication_socket[LISTEN_FD])
    {
        throw std::runtime_error("server acccept");
    }

    m_epoll.add(data->m_communication_socket[LISTEN_FD]);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                  execute_tcp_communication */
/*                                                  ~~~~~~~~~~~~~~~~~~~~~~~~~ */
void TCPServer::execute_tcp_communication(std::shared_ptr<ThreadData> data)
{
    configure_socket(data);
    wait_for_client(data);
    communicate_with_tcp_client(data);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                  execute_udp_communication */
/*                                                  ~~~~~~~~~~~~~~~~~~~~~~~~~ */
void TCPServer::execute_udp_communication(std::shared_ptr<ThreadData> data)
{
    configure_socket(data);
    communicate_with_udp_client(data);    
}


} // namespace med
