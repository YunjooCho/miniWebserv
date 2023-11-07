//
// Created by llx on 2018/8/12.
//

// Implementation of the ServerSocket class

#include "ServerSocket.h"
#include "SocketException.h"


ServerSocket::ServerSocket ( int port )
{
    if ( ! Socket::create() )
    {
        throw SocketException ( "Could not create server socket." );
    }

    if ( ! Socket::bind ( port ) )
    {
        throw SocketException ( "Could not bind to port." );
    }

    if ( ! Socket::listen() )
    {
        throw SocketException ( "Could not listen to socket." );
    }

    if ( ! Socket::set_non_blocking() ) //! Set Non-blocking to server socket
    {
        throw SocketException ( "Could not set non-blocking to server socket." );
    }
}

ServerSocket::~ServerSocket()
{
}


const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
    if ( ! Socket::send ( s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }

    return *this;

}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}

void ServerSocket::accept ( ServerSocket& sock )
{
    if ( ! Socket::accept ( sock ) )
    {
        throw SocketException ( "Could not accept socket." );
    }
}

void ServerSocket::kqueue ( void )
{
    if ( ! Socket::kqueue() )
    {
        throw SocketException ( "Could not create kqueue." );
    }
}

void ServerSocket::kevent ( const struct timespec *timeout )
{
    if ( ! Socket::kevent( timeout ) )
    {
        throw SocketException ( "Could not excute kevent()" );
    }
}