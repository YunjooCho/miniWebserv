//
// Created by llx on 2018/8/12.
//

#ifndef MPC_SOCKET_H
#define MPC_SOCKET_H
// Definition of the Socket class


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <map>

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 100;
const int MAXRECV = 1000;

class Socket
{
	public:
		Socket();
		virtual ~Socket();

		// Server initialization
		bool    create();
		bool    bind ( const int port );
		bool    listen() const;
		bool    accept ( Socket& ) const;
		bool    set_non_blocking ( void );

		// Client initialization
		bool    connect ( const std::string host, const int port );

		// Data Transimission
		bool    send ( const std::string ) const;
		int     recv ( std::string& ) const;

		bool    is_valid( void ) const { return m_sock != -1; }

		const int&          getSocketFd(void);
		const sockaddr_in&  getSockAddr(void);
	protected:
		int         m_sock;
		sockaddr_in m_addr;
};



#endif //MPC_SOCKET_H
