/**
 * Netry is a high level networking implementation of The Single UNIX Specification, Version 2.
 * @see: http://pubs.opengroup.org/onlinepubs/7908799/xnsix.html
 */
//
// Created by mz on 22/10/17.
//

#ifndef NETRY_SOCKET_H
#define NETRY_SOCKET_H

#include <string>
#include <netinet/in.h> // Internet Protocol family
#include <arpa/inet.h> // Definitions for internet operations
#include <unistd.h>
#include "../include/SocketException.h"

namespace netry {

    class Socket {

    private:
        std::string address; // The target address to connect with
        int port;
        int fileDescriptor; // FD
        // The sockaddr_in structure is used to store addresses for the Internet protocol family.
        // Values of this type must be cast to struct sockaddr for use with the fileDescriptor interfaces
        struct sockaddr_in socketAddress;

    public:

        Socket();

        explicit Socket(int fileDescriptor) throw(SocketException);

        Socket(const std::string &address, int port) throw(SocketException);

        void bind(const std::string &address, int port) throw(SocketException);

        /**
        * Destroy the client socket and closes the File Descriptor (FD)
        * Wait to close until all data is transmitted.
        */
        void close();

        void setFileDescriptor(int fileDescriptor);

        int getFileDescriptor() const;
    };
}


#endif // NETRY_SOCKET_H
