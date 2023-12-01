#ifndef ISERVERSOCKET_HPP
#define ISERVERSOCKET_HPP

#include <sys/socket.h>

#include <iostream>

class IServerSocket {
 public:
  // socket
  virtual void socket(int domain, int type, int protocol) = 0;
  virtual void bind(int sockfd, const struct sockaddr *addr,
                    socklen_t addrlen) = 0;
  virtual void listen(int sockfd, int backlog) = 0;
  virtual void accept(int sockfd, struct sockaddr *addr,
                      socklen_t *addrlen) = 0;
  virtual void close(int socketFd) = 0;
};

#endif