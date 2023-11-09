//
// Created by llx on 2018/8/12.
//

#ifndef MPC_SERVERSOCKET_H
#define MPC_SERVERSOCKET_H

# include <iostream>
# include "Socket.h"
# include "Kqueue.h"

class ServerSocket : public Socket
{
    public:
        ServerSocket( int port );
        ServerSocket(){};
        virtual ~ServerSocket();

        const ServerSocket& operator << ( const std::string& ) const;
        const ServerSocket& operator >> ( std::string& ) const;

        void	accept(ServerSocket&);
        void	deleteClient(int clientFd);
    private:
        std::map<int, std::string> m_clients;

};


#endif //MPC_SERVERSOCKET_H
