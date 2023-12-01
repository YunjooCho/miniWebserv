#ifndef CUSTOMKQUEUE_H
# define CUSTOMKQUEUE_H

# include <iostream>
# include <vector>
# include <unistd.h>
# include <sys/event.h>
# include <sys/ioctl.h>

class Kqueue
{
	public:
		int													m_kqFd;         // kqueue의 파일디스크립터
		std::vector<struct kevent>	m_changeList;   // 
		int													m_newEvents;    // 현 시점에 처리할 수 있는 이벤트 개수
		struct kevent								m_eventList[8]; // 현 시점에 처리할 수 있는 

		Kqueue();
		~Kqueue();

		int							getNewEvents(void);                                                       // 멤버변수인 m_newEvents 의 getter
		struct kevent*	getCurrEvent(int idx);                                                    // 멤버변수인 m_eventList 배열에서 인자로 받은 인덱스에 위치한 이벤트(?)를 가져옴
		void						kqueue(void);                                                             // kqueue를 생성하고 실패 시 throw
		void						kevent(const struct timespec *timeout);
		void						change_events(uintptr_t ident, int16_t filter, \
																	uint16_t flags, uint32_t fflags, intptr_t data, void *udata); // 멤버변수인 m_changeList에 EV_SET()(매크로 함수)를 통해 이벤트를 등록, 수정, 삭제함
		void						changeListClear(void);                                                    // 
};

#endif