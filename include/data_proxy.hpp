#ifndef _DATA_PROXY_
#define _DATA_PROXY_
/*******************************************************************************
*                             data proxy
*                       =====================
* File Name: data_proxy.hpp
* Related files: data_proxy.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 6.11.19
* Last update: 6.11.19
*******************************************************************************/


#include <string>
#include <fstream>

namespace med
{

class DataProxy
{
    public:
        DataProxy(std::string name_of_output_file = "server_output.txt");
        ~DataProxy();

        DataProxy(const DataProxy&) = delete;
        DataProxy& operator=(const DataProxy&) = delete;
        DataProxy(const DataProxy&&) = delete;
        DataProxy& operator=(const DataProxy&&) = delete;

        // write to an already existing log file 
        void write_to_file(const std::string& string);

    private:
        std::ofstream m_file;
};

} // // namespace hrd9
#endif // _DataProxy_
