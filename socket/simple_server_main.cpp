#include <iostream>
#include <string>

#include "ServerSocket.h"
#include "SocketException.h"

int main(int argc, char** argv) {
  std::cout << "running....\n";

  try {
    // Create the socket
    ServerSocket server(30000);

    kqueue(); //! 서버 클래스, 소켓 클래스 수정
    change_events(server, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    while (true) {
      kevent(NULL);
      change_list.clear();
      for (size_t i = 0; i < new_events) //TODO
      ServerSocket new_sock;

      server.accept(new_sock);
      std::cout << "accept" << std::endl;
      try {
        while (true) {
          std::string data;
          new_sock >> data; //Socket에 담긴 값을 data에 가져옴
          new_sock << data;
        }
      } catch (SocketException&) {
      }
    }
  } catch (SocketException& e) {
    std::cout << "Exception was caught:" << e.description() << std::endl;
    std::cout << "Exiting." << std::endl;
  }

  return 0;
}