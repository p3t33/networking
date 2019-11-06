/*******************************************************************************
*                           epoll wrapper
*                       =====================
* File Name: epoll_wrapper.cpp
* Related files: epoll_wrapper.hpp
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
#include <iostream>
#include <assert.h> /* assert */ 
#include <sys/epoll.h> // epoll
#include <unistd.h>    // for close()

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "include/epoll_wrapper.hpp"
/*============================================================================*/
namespace med
{

/*============================================================================*/
/*                               Class EPollWrapper                           */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*  									                             Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
// The epoll_size argument specifies the number of file descriptors that
// we expect to monitor his argument is not an upper limit, but rather
//  a hint to the kernel about how to initially dimension internal
//  data structures. (Since Linux 2.6.8, the size argument is ignored)

EPollWrapper::EPollWrapper(int epoll_flags, int max_event):
                                    m_epoll_fd(epoll_create1(epoll_flags)),
                                    m_max_event(max_event)
{
   m_epoll_events = new epoll_event[m_max_event];
   m_epoll_events->events = EPOLLIN;
   m_epoll_events->data.fd = 0;
}
                                                                
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*  									                              Destructor / dtor */
/*                                                          ~~~~~~~~~~~~~~~~~ */
 EPollWrapper::~EPollWrapper()
 {
    close(m_epoll_fd);
    delete[] m_epoll_events;
 }

/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~                             */
/*                               member functions                             */
/*                               ~~~~~~~~~~~~~~~~                             */

//epoll_ctl is used to add, remove, or otherwise control the monitoring of
// an fd in the set 

/*                                                                        add */
/*                                                                        ~~~ */
void EPollWrapper::add(int file_descriptor_to_add,  int events_flag)
{

   struct epoll_event new_event = {};

   new_event.data.fd = file_descriptor_to_add;
   new_event.events = events_flag;

   epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, file_descriptor_to_add, &new_event);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                     remove */
/*                                                                     ~~~~~~ */
void EPollWrapper::remove(int file_descriptor_to_remove)
{
   epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, file_descriptor_to_remove, nullptr);
}  

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                       wait */
/*                                                                       ~~~~ */
// The size of the array is given by the maxevents argument 
// The timeout argument specifies the time to wait for an
// event, in milliseconds; a value of -1 means to wait indefinitely.
int EPollWrapper::wait(int maxevents, int time_out_ms)
{
   int event_count = epoll_wait(m_epoll_fd,
                                m_epoll_events,
                                maxevents,
                                time_out_ms);

   if(-1 == event_count)
   {
      throw std::runtime_error("epoll_wait fail\n"); 
   }

   return (event_count);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                 operator[] */
/*                                                                 ~~~~~~~~~~ */
const epoll_event& EPollWrapper::operator[](const int index)
{
    return m_epoll_events[index];
}

} // namespace med
