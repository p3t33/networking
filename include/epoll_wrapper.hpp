#ifndef EPOOL_WRAPPER
#define EPOOL_WRAPPER
/*******************************************************************************
*                           epoll wrapper
*                       =====================
* File Name: epoll_wrapper.hpp
* Related files: epoll_wrapper.cpp
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 6.11.19
* Last update: 9.11.19
*******************************************************************************/

#include <cstddef> //size_t
#include <vector> // vector
#include <sys/epoll.h>

namespace med
{

class EPollWrapper
{
public:
	EPollWrapper(bool multithread_flag = false ,
                 int create_flag = 0,
                 int max_event = 20);
	~EPollWrapper();

    EPollWrapper(const EPollWrapper&) = delete;
    EPollWrapper& operator=(const EPollWrapper&) = delete;

    // Interface / API
    // ------------------------------------------------------------------
    void add(int file_descriptor_to_add,
             uint32_t events_flag = (EPOLLET | EPOLLIN));
    void remove(int file_descriptor_to_remove);
    // time_out_ms = -1 makes epoll block “forever”
    int wait(epoll_event* epoll_events, int maxevents = 10, int time_out_ms = -1);
    const epoll_event& operator[](const int index);

private: 
    // managing variables 
    // -------------------------------------------------------------
    int m_epoll_fd;
    int m_max_event;
    bool m_multithread_flag;

    // when epoll_wait returns it filles <m_epoll_events> array with 
    // epoll_event structs that are ready to be to read from.
    //
    // pointer is used because number events determented in run time.
    struct epoll_event* m_epoll_events;
};

}// namespace med

#endif // EPOOL_WRAPPER
