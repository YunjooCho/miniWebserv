#include <iostream>
#include <string>

#include "ServerSocket.h"
#include "SocketException.h"

int main(int argc, char** argv) {
  std::cout << "running....\n";

  try {
    // Create the socket
    ServerSocket server(30000);

    while (true) {
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