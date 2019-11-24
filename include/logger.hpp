#ifndef _LOGGER_
#define _LOGGER_
/*******************************************************************************
*                             Logger
*                       =====================
* File Name: logger.hpp
* Related files: logger.hpp logger_test.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 24.11.19
* Last update: 24.11.19
*******************************************************************************/


#include <string>
#include <fstream>

namespace med
{

class Logger
{
    public:
        Logger(std::string log_name = "log_txt");
        ~Logger();

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(const Logger&&) = delete;
        Logger& operator=(const Logger&&) = delete;

        // write to an already existing log file 
        void write_to_log(const std::string& file_name,
                          const std::string& text,
                          size_t line_number);

    private:
        std::ofstream m_log_file; // write only mode
};

} // // namespace med
#endif // _LOGGER_