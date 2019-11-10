/*******************************************************************************
*                              data proxy
*                       =====================
* File Name: data_proxy.cpp
* Related files: data_proxy.hpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 6.11.19
* Last update: 11.11.19
*******************************************************************************/


/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <iostream>

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "./include/data_proxy.hpp"

/*============================================================================*/
namespace med
{

/*============================================================================*/
/*                                  Class DataProxy                              */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
DataProxy::DataProxy(std::string name_of_output_file)
{
    m_file.open(name_of_output_file, std::ofstream::app);
}
                                                                    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
DataProxy::~DataProxy()
{
    m_file.close();
}

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */
/*                                                              write_to_file */
/*                                                              ~~~~~~~~~~~~~ */
void DataProxy::write_to_file()
{
    // pop _end_of_file_ from the vector
    m_data.pop_back();


    std::cout << "client sent " << m_data.size() << " words" << std::endl;
    std::cout << "=========================================" << std::endl;

    for (auto iterator: m_data)
    {
        //m_file << std::flush;
        m_file << iterator.c_str() << " ";
        m_file << std::endl;
    }

    // std::cout << "============= Statistics ================" << std::endl;
}


void DataProxy::gate_way(const std::string& string)
{
    m_data.push_back(string);
}

} // namespace med
