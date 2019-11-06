/****************************************************************
*                              client
*                       =====================
* File Name: client.cpp  
* Related files: tcp_client.cpp tcp_client.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 5.11.19
* Last update: 6.11.19
*******************************************************************************/

#include <iostream>
#include "./include/tcp_client.hpp"
using namespace med;

int main(int argc, char const *argv[])
{
    if (1 == argc)
    {
        std::cout<<"please provide an a port number: ";
        std::cout<<"client.out <number of port>" <<std::endl;
    
        return (0);
    }

    try
    {
        //TCPClient test;
        TCPClient client(argv[1], argv[2], argv[3]);
        client.communicate_with_server();
    }
    catch(const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return (1);
    }
    
    return (0);
}
