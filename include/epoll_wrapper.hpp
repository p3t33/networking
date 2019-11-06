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
* Last update: 6.11.19
*******************************************************************************/

#include <cstddef> //size_t
#include <vector> // vector
#include <sys/epoll.h>

namespace med
{

class EPollWrapper
{
public:
	EPollWrapper(int epoll_flags = 0,
                 int max_event = 10,
                 int event_flag = EPOLLIN);
	~EPollWrapper();

    EPollWrapper(const EPollWrapper&) = delete;
    EPollWrapper& operator=(const EPollWrapper&) = delete;

    // Interface / API
    // ------------------------------------------------------------------
    void add(int file_descriptor_to_add, int events_flag = EPOLLIN);
    void remove(int file_descriptor_to_remove);
    int wait(int maxevents = 10, int time_out_ms = 5000);
    const epoll_event& operator[](const int index);
    // ------------------------------------------------------------------

private: 
    int m_epoll_fd;
    int m_max_event;

    // TODO: maybe add a vector instead of array
    // when epoll_wait returns it filles <m_epoll_events> array with 
    // epoll_event structs that are ready to be to read from.
    struct epoll_event* m_epoll_events;
};

}// namespace med

#endif // EPOOL_WRAPPER
