#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <iostream>
#include <map>

#include "IServerSocket.hpp"
#include "Kqueue.hpp"

class ServerSocket : public IServerSocket {
 public:
  ServerSocket(const int& port);
  ServerSocket(const std::string& ipAddr, const int& port);
  ~ServerSocket();

 private:
  int													m_socketFd;
  sockaddr_in									m_addr;
  std::map<int, std::string>	m_clientList;

  ServerSocket();                            // TODO - 필요 시 public
  ServerSocket(const ServerSocket& socket);  // TODO - 필요 시 public
  ServerSocket& operator=(const ServerSocket& socket);  // TODO - 필요 시 public
};

#endif