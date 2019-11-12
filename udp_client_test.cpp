/****************************************************************
*                              client
*                       =====================
* File Name: udp_client_test.cpp  
* Related files: udp_client.cpp udp_client.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 12.11.19
* Last update: 12.11.19
*******************************************************************************/

#include <iostream>
#include "./include/udp_client.hpp"
using namespace med;

int main()
{
    try
    {
        UDPClient client;
 
        client.communicate_with_server();
    }
    catch(const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return (1);
    }
    
    return (0);
}
