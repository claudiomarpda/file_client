/**
 * Netry is a high level networking implementation of The Single UNIX Specification, Version 2.
 * @see: http://pubs.opengroup.org/onlinepubs/7908799/xnsix.html
 */
//
// Created by mz on 22/10/17.
//

#include <iostream>
#include <stdint-gcc.h>
#include "../include/Socket.h"

netry::Socket::Socket() = default;

netry::Socket::Socket(int fileDescriptor) throw(SocketException) : fileDescriptor(fileDescriptor) {}

netry::Socket::Socket(const std::string &address, int port) throw(SocketException): address(address), port(port) {
    bind(address, port);
}

void netry::Socket::bind(const std::string &address, int port) throw(SocketException){
    const char *serverAddressChars = address.c_str();

    // Set the server IP address
    // Convert address from text to binary form
    if (inet_pton(AF_INET, serverAddressChars, &socketAddress.sin_addr.s_addr) < 0) {
        throw SocketException("Failed to set server IP address: " + address);
    }

    fileDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check if the connection is valid
    if (fileDescriptor < 0) {
        throw SocketException("Error creating client fileDescriptor");
    }

    socketAddress.sin_family = AF_INET;
    auto port_16bits = static_cast<uint16_t>(port);
    socketAddress.sin_port = htons(port_16bits);

    int connectionResult = connect(fileDescriptor, (struct sockaddr *) &socketAddress, sizeof(socketAddress));
    int errorSaved = errno;
    if (connectionResult < 0) {
        std::string errorMsg = "Connection to the server failed. errno code " + std::to_string(errorSaved);
        throw SocketException(errorMsg);
    }
}

/**
 * Destroy the client socket and closes the File Descriptor (FD)
 * Wait to close until all data is transmitted.
 */
void netry::Socket::close() {
    ::close(fileDescriptor);
}

void netry::Socket::setFileDescriptor(int fileDescriptor) {
    Socket::fileDescriptor = fileDescriptor;
}

int netry::Socket::getFileDescriptor() const {
    return fileDescriptor;
}




