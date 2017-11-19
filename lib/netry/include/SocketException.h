/**
 * Netry is a high level networking implementation of The Single UNIX Specification, Version 2.
 * @see: http://pubs.opengroup.org/onlinepubs/7908799/xnsix.html
 */
//
// Created by mz on 22/10/17.
//

#ifndef NETRY_SOCKETEXCEPTION_H
#define NETRY_SOCKETEXCEPTION_H

#include <stdexcept>

namespace netry {

    class SocketException : public std::runtime_error {

    public:
        explicit SocketException(const std::string &__arg) : runtime_error(__arg) {}
    };
}

#endif // NETRY_SOCKETEXCEPTION_H
