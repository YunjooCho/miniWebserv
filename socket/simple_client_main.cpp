#include <iostream>
#include <string>

#include "ClientSocket.h"
#include "SocketException.h"

int main(int argc, char** argv) {
  try {
    ClientSocket client_socket("localhost", 30000);

    std::string reply;

    try 
    {
      client_socket << "Test message.";
      client_socket >> reply;
    } 
    catch (SocketException&) 
    {
    }

    std::cout << "We received this response from the server: " << reply << std::endl;

  } 
  catch (SocketException& e) 
  {
    // TODO - 소켓 연결이 실패한 경우, 소켓을 닫고 다시 새 소켓을 만들어야 함 -> throw 때문에 자동으로 스택에서 인스턴스 제거?
    std::cout << "Exception was caught:" << e.description() << std::endl;
  }

  return 0;
}