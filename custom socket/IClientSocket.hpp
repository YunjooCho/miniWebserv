#ifndef ICLIENTSOCKET_HPP
# define ICLIENTSOCKET_HPP

# include <iostream>
# include <sys/socket.h>

class IClientSocket
{
	//socket
	virtual void	socket(int domain, int type, int protocol, int kqFd) = 0;
	virtual void	connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) = 0;
	virtual void	close(int socketFd) = 0;
};

#endif