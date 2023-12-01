#include "Kqueue.h"

Kqueue::Kqueue() : m_kqFd(-1) {}

Kqueue::~Kqueue() 
{ 
	if (m_kqFd != -1)
		close(m_kqFd);
}

int Kqueue::getNewEvents(void) { return (m_newEvents); }

struct kevent *Kqueue::getCurrEvent(int idx) { return (&m_eventList[idx]); }

void Kqueue::kqueue(void) {
  m_kqFd = ::kqueue();

  if (m_kqFd == -1) 
		throw std::runtime_error("Could not create kqueue.");
}

void Kqueue::change_events(uintptr_t ident, int16_t filter, uint16_t flags,
                           uint32_t fflags, intptr_t data, void *udata) {
  struct kevent temp_event;

  EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
  m_changeList.push_back(temp_event);
}

void Kqueue::kevent(const struct timespec *timeout) {
  m_newEvents = ::kevent(m_kqFd, &m_changeList[0], m_changeList.size(),
                         m_eventList, 8, timeout);
  if (m_newEvents == -1) 
		throw std::runtime_error("Could not process kevent.");

  // debugging
  // std::cout << "m_newEvents : " << m_newEvents << std::endl;
}

void Kqueue::changeListClear(void) { m_changeList.clear(); }