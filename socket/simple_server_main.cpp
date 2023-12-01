#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "Kqueue.h"
#include "ServerSocket.h"
#include "SocketException.h"

int main(int argc, char** argv) {
  std::cout << "running....\n";

  try {
    // Create the socket
    ServerSocket server(30000);
    ServerSocket connect_socket;
    Kqueue kq;
    struct kevent* curr_event;

    kq.kqueue();  //! 서버 클래스, 소켓 클래스 수정
    kq.change_events(server.getSocketFd(), EVFILT_READ, EV_ADD | EV_ENABLE, 0,
                     0, NULL);
    while (true) {
      kq.kevent(NULL);
      kq.changeListClear();
      for (size_t i = 0; i < kq.getNewEvents(); i++) {
        curr_event = kq.getCurrEvent(i);

        // //debugging
        // std::cout << "============================================" <<
        // std::endl; std::cout << "ident:  " << curr_event->ident << std::endl;
        // std::cout << "filter: " << curr_event->filter << std::endl;
        // std::cout << "flags: " << curr_event->flags << std::endl;
        // std::cout << "fflags: " << curr_event->fflags << std::endl;
        // std::cout << "data: " << curr_event->data << std::endl;
        // // std::cout << "udata: " << curr_event->udata << std::endl;
        // std::cout << "============================================" <<
        // std::endl;

        if (curr_event->flags & EV_ERROR)  // 1. flag가 활성화 되어 있고 ERROR
                                           // 일 때 // TODO - 왜 매크로?
        {
          if (curr_event->ident ==
              server.getSocketFd())  // 1-1.리슨 소켓(서버) 에러 - 에러메시지
                                     // 출력 후 종료
          {
            std::cerr << "Listen Socket Error" << std::endl;
            exit(EXIT_FAILURE);
          } else  // 1-2.연결 소켓(클라이언트) 에러 - 에러메시지 출력 후 연결
                  // 해제
          {
            std::cerr << "Connect Socket Error" << std::endl;
            server.deleteClient(curr_event->ident);
          }
        } else if (curr_event->filter ==
                   EVFILT_READ)  // 2. READ 이벤트가 활성화된 경우
        {
          if (curr_event->ident ==
              server.getSocketFd())  // 2-1. 이벤트 주체가 리슨 소켓(서버)인
                                     // 경우 - 요청을 accept()
          {
            try {
              server.accept(connect_socket);
              std::cout << "accept" << std::endl;
              fcntl(connect_socket.getSocketFd(), F_SETFL, O_NONBLOCK,
                    FD_CLOEXEC);

              kq.change_events(connect_socket.getSocketFd(), EVFILT_READ,
                               EV_ADD | EV_ENABLE, 0, 0, NULL);
              kq.change_events(connect_socket.getSocketFd(), EVFILT_WRITE,
                               EV_ADD | EV_ENABLE, 0, 0, NULL);
              server.setClientDate(connect_socket.getSocketFd(), "");
            } catch (SocketException& e) {
              std::cout << "Exception was caught:" << e.description()
                        << std::endl;
            }
          } else if (server.findClient(
                         curr_event->ident))  // 2-2. 이벤트 주체가 연결
                                              // 소켓(클라이언트)인 경우 - 연결
                                              // 소켓에 담긴 내용을 읽어들임
          {
            char buf[1024];
            int n = read(curr_event->ident, buf, sizeof(buf));

            if (n <= 0)  // 2-2-1. 연결 소켓의 내용 읽기를 실패한 경우 -
                         // 에러메시지 반환하고 연결 해제
            {
              if (n < 0) std::cerr << "Client Read Error" << std::endl;
              server.deleteClient(curr_event->ident);
            } else  // 2-2-2. 연결 소켓의 내용 읽기를 성공한 경우 - 읽어들인
                    // 내용(HTTP 메시지)을 서버의 멤버변수인 m_clients 맵에 저장
            {
              buf[n] = '\0';
              server.setClientDate(connect_socket.getSocketFd(), buf);
            }
          }
        } else if (curr_event->filter ==
                   EVFILT_WRITE)  // 3. WRITE 이벤트가 활성화된 경우
        {
          server.handleWriteEvent(
              curr_event->ident);  // 3-1. write() 함수를 실행하여 실패하는 경우
                                   // 에러메시지를 출력 3-2. 성공하면 map 의
                                   // data 를 비움
        }
      }
    }
  } catch (SocketException& e) {
    std::cout << "Exception was caught:" << e.description() << std::endl;
    std::cout << "Exiting." << std::endl;
  }

  return (0);
}