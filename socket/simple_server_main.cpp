#include <iostream>
#include <string>

#include "ServerSocket.h"
#include "SocketException.h"
#include "Kqueue.h"


int main(int argc, char** argv) {
  std::cout << "running....\n";

  try {
    // Create the socket
    ServerSocket server(30000);

    Kqueue  kq;
    kq.kqueue(); //! 서버 클래스, 소켓 클래스 수정
    kq.change_events(server.getSocketFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    while (true) {
      kq.kevent(NULL);
      kq.changeListClear();
      for (size_t i = 0; i < kq.getNewEvents(); i++)
      {
        struct kevent* curr_event = kq.getCurrEvent(i);

        //debugging
        std::cout << "============================================" << std::endl;
        std::cout << "ident:  " << curr_event->ident << std::endl;
        std::cout << "filter: " << curr_event->filter << std::endl;
        std::cout << "flags: " << curr_event->flags << std::endl;
        std::cout << "fflags: " << curr_event->fflags << std::endl;
        std::cout << "data: " << curr_event->data << std::endl;
        // std::cout << "udata: " << curr_event->udata << std::endl;
        std::cout << "============================================" << std::endl;

        if (curr_event->flags & EV_ERROR) // TODO - 왜 매크로?
        {
          if (curr_event->ident == server.getSocketFd())
          {
            std::cout << "Listen Socket Error" << std::endl;
            exit(EXIT_FAILURE);
          }
          else
          {
            std::cout << "Connect Socket Error" << std::endl;
            close(curr_event->ident);
            server.deleteClient(curr_event->ident);
          }
        }
        else if (curr_event->filter == EVFILT_READ)
        {
			if (curr_event->ident == server.getSocketFd())
			{
				try
				{
					ServerSocket connect_socket;
					server.accept(connect_socket);
					std::cout << "accept" << std::endl;
				}
				catch(SocketException&) {}
			
			}
		}
	}

      // try {
      //   while (true) {
      //     std::string data;
      //     new_sock >> data; //Socket에 담긴 값을 data에 가져옴
      //     new_sock << data;
      //   }
      // } catch (SocketException&) {
      // }
    }
  } catch (SocketException& e) {
    std::cout << "Exception was caught:" << e.description() << std::endl;
    std::cout << "Exiting." << std::endl;
  }

  return 0;
}