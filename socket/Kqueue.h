#ifndef CUSTOMKQUEUE_H
# define CUSTOMKQUEUE_H

# include <iostream>
# include <sys/event.h>
# include <vector>

class Kqueue
{
	public:
		int							m_kqFd;
		int							m_newEvents;
		std::vector<struct kevent>	m_changeList;
		struct kevent				m_eventList[8];

		Kqueue();
		~Kqueue();

		int				getNewEvents(void);
		struct kevent*	getCurrEvent(int idx);
		void			kqueue(void);
		void			kevent(const struct timespec *timeout);
		void			change_events(uintptr_t ident, int16_t filter, \
							uint16_t flags, uint32_t fflags, intptr_t data, void *udata);
		void			changeListClear(void);
};

#endif