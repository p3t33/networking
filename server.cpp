/*******************************************************************************
*                              server
*                       =====================
* File Name: server.cpp  
* Related files: tcp_server.cpp tcp_server.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 5.11.19
* Last update: 6.11.19
*******************************************************************************/

#include <iostream>
#include "./include/tcp_server.hpp"
using namespace med;

int main()
{
    try
    {
        TCPServer test;
        test.communicate_with_client();
    }
    
    catch(const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return (1);
    }
    
    return (0);
}
