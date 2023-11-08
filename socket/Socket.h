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
#include <vector>
#include <sys/event.h>
#include <map>

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 100;
const int MAXRECV = 1000;

static int                        kqfd;
static int                        new_events;
static std::vector<struct kevent> change_list;
struct kevent*                    curr_event;
struct kevent                     event_list[8];


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
        void    change_events( uintptr_t ident, int16_t filter, \
                    uint16_t flags, uint32_t fflags, intptr_t data, void *udata );
        bool    kevent( const struct timespec *timeout );

        // Client initialization
        bool    connect ( const std::string host, const int port );

        // Kqueue initialization
        bool    kqueue(void);

        // Data Transimission
        bool    send ( const std::string ) const;
        int     recv ( std::string& ) const;

        bool    is_valid( void ) const { return m_sock != -1; }

    private:
        int         m_sock;
        sockaddr_in m_addr;
};



#endif //MPC_SOCKET_H
