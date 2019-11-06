/*******************************************************************************
*                           data proxy test
*                       =====================
* File Name: data_proxy_test.cpp
* Related files: data_proxy.cpp data_proxy.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 6.11.19
* Last update: 6.11.19
*******************************************************************************/

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream> // std::cout

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "../include/data_proxy.hpp"
using namespace med;

/*                                                           global variables */
/*                                                           ~~~~~~~~~~~~~~~~ */
static const size_t write_iterators = 3;
static const char name_of_file[] = "demo.txt";

/*============================================================================*/
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                             Forward declaration                            */
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                                                                 Unit tests */
/*                                                                 ~~~~~~~~~~ */
static void unit_test_write_to_file(void);

/*============================================================================*/

int main()
{
    unit_test_write_to_file();

    return(0);
}

/*============================================================================*/
/*                                  unit_tests                                */
/*============================================================================*/
/*                                                     unit_test_write_to_file */
/*                                                     ~~~~~~~~~~~~~~~~~~~~~~ */

static void unit_test_write_to_file(void)
{  
    std::cout << "============ unit_test_write_to_file ============"<< std::endl;
    DataProxy demo(name_of_file);

    for (size_t i = 0; i < write_iterators; ++i)
    {
        demo.write_to_file("hello");
    }

    std::cout << write_iterators << " iterators were written to: " 
              << name_of_file << " file" << std::endl;

    std::cout << "================================================"<< std::endl;
}
