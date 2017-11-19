/**
 * Netry is a high level networking implementation of The Single UNIX Specification, Version 2.
 * @see: http://pubs.opengroup.org/onlinepubs/7908799/xnsix.html
 */
//
// Created by mz on 22/10/17.
//

#ifndef NETRY_NETSTREAM_H
#define NETRY_NETSTREAM_H

#include <netinet/in.h> // Internet Protocol family
#include <arpa/inet.h> // Definitions for internet operations
#include <unistd.h>
#include <string>
#include "Socket.h"

namespace netry {

    /**
     * Uses a Socket File Descriptor to send data to an endpoint.
     */
    class NetStream {

        const unsigned int kStringEndLength = 1;

    private:
        Socket socket;

    public:

        NetStream();

        // Explicit keyword prevents the compiler from using this constructor for implicit conversions
        explicit NetStream(const Socket &socket);

        /**
        * Write bytes to a socket endpoint
        * @param bytes
        * @param size
        */
        void writeBytes(const char *bytes, size_t n) const;

        ssize_t readBytes(char buffer[]) const;

        /**
        * Writes a string to a socket endpoint
        */
        void writeString(const std::string &message) const ;

        /**
        * Receive a string from a socket stream
        * <p>
        * @return the received string
        */
        std::string readString() const;

        /**
         * Writes an integer value to an endpoint
         */
        void writeInt(int data) const;

        /**
         * Receives an integer value from a socket stream
         */
        int readInt() const;

        const Socket &getSocket() const;

        void setSocket(const Socket &socket);
    };
}


#endif // NETRY_NETSTREAM_H
