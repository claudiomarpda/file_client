/**
 * Netry is a high level networking implementation of The Single UNIX Specification, Version 2.
 * @see: http://pubs.opengroup.org/onlinepubs/7908799/xnsix.html
 */
//
// Created by mz on 22/10/17.
//

#ifndef NETRY_SERVERSOCKET_H
#define NETRY_SERVERSOCKET_H

#include <netinet/in.h> // Internet Protocol family
#include <arpa/inet.h> // Definitions for internet operations
#include <cstring>
#include <unistd.h>
#include "SocketException.h"
#include "Socket.h"

namespace netry {

    /**
     * Allows to wait for clients connections with networking sockets.
     * Config: IPv4 internet address and TCP protocol.
     */
    class ServerSocket {

    private:
        int serverSocketFd; // File Descriptor
        struct sockaddr_in serverAddress; // Describes an internet socket address
        socklen_t addressSize;
        int port; // Number of the port where it will be listening

    public:

        ServerSocket();

        // Explicit keyword prevents the compiler from using this constructor for implicit conversions
        /**
        * Constructor that binds the socket and the address of the server.
        */
        explicit ServerSocket(int port) throw(SocketException);


        /**
        * Creates a socket end point for communication and defines the socket address structure (sockaddr_in).
        *
        * @param port: where the server will be listening for client connection
        */
        void bind(int port) throw(SocketException);

        /**
        * Accept a client connection to the socket previously created.
        * The process will stay idle (waiting) until a client connection is made.
        */
        netry::Socket accept() throw(SocketException);

        /**
        * Closes the File Descriptor (FD) of the server
        * Wait to close until all data is transmitted.
        */
        void close();

    };
}

#endif // NETRY_SERVERSOCKET_H