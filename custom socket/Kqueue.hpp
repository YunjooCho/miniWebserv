#ifndef CKQUEUE_HPP
#define CKQUEUE_HPP

#include <sys/event.h>
#include <sys/types.h>

#include <vector>

class Kqueue {
 public:
  void kqueue(void);
  void changeEvents(uintptr_t ident, int16_t filter, uint16_t flags,
                    uint32_t fflags, intptr_t data, void *udata);

 private:
  int													m_kqFd;
  int													new_events;
  std::vector<struct kevent>	m_changeList;
  struct kevent								m_eventList[8];
  struct kevent								*m_currEvent;
};

#endif