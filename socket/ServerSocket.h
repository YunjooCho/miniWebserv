//
// Created by llx on 2018/8/12.
//

#ifndef MPC_SERVERSOCKET_H
#define MPC_SERVERSOCKET_H

#include "Socket.h"

class ServerSocket : protected Socket
{
    public:
        ServerSocket ( int port );
        ServerSocket (){};
        virtual ~ServerSocket();

        const ServerSocket& operator << ( const std::string& ) const;
        const ServerSocket& operator >> ( std::string& ) const;

        void accept ( ServerSocket& );
        void kqueue ( void );
        void kevent ( const struct timespec *timeout );
    private:
        std::map<int, std::string> m_clients;

};


#endif //MPC_SERVERSOCKET_H
