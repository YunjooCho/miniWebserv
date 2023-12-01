#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <iostream>
#include <map>

#include "IClientSocket.hpp"

class ClientSocket : public IClientSocket {
 public:
  ClientSocket(const std::string& ipAddr, const int& port, const int& kqFd);
  ~ClientSocket();

 private:
  int 				m_socketFd;
  sockaddr_in m_addr;

  ClientSocket();                                       // TODO - 필요 시 public
  ClientSocket(const ClientSocket& socket);             // TODO - 필요 시 public
  ClientSocket& operator=(const ClientSocket& socket);  // TODO - 필요 시 public
};

#endif