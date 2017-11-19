/**
 * Netry is a high level networking implementation of The Single UNIX Specification, Version 2.
 * @see: http://pubs.opengroup.org/onlinepubs/7908799/xnsix.html
 */
//
// Created by mz on 22/10/17.
//

#include <stdint-gcc.h>
#include "../include/ServerSocket.h"

netry::ServerSocket::ServerSocket() = default;

/**
 * Constructor that binds the socket and the address of the server.
 */
netry::ServerSocket::ServerSocket(int port) throw(SocketException) : port(port) {
    bind(port);
}

/**
 * Creates a socket end point for communication and defines the socket address structure (sockaddr_in).
 *
 * @param port: where the server will be listening for client connection
 */
void netry::ServerSocket::bind(int port) throw(SocketException) {

    // Creates an endpoint for communication
    // AF_INET: IPv4 internet address of 32 bits
    // SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams
    // IPPROTO_TCP: TCP protocol
    serverSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocketFd < 0) {
        throw SocketException("Could not create the File Descriptor");
    }

    const int option = 1;
    // Makes possible to listen in the same port without delay
    // SOL_SOCKET: set options at the socket level
    // SO_REUSEADDR: avoids the port to be on CLOSE_WAIT state after closing it
    setsockopt(serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    // Defines address structure

    // Internet protocol: IPv4 address of 32 bits
    serverAddress.sin_family = AF_INET;

    // htons() converts 16-bit and 32-bit quantities between network byte order and host byte order
    // Returns the argument value converted from host to network byte order
    // INADDR_ANY: Address to accept any incoming messages
    serverAddress.sin_addr.s_addr = htons(INADDR_ANY);
    auto port_16bits = static_cast<uint16_t>(port);
    serverAddress.sin_port = htons(port_16bits);

    // Bind the socket to the local address
    // Associate our server socket FD with an address and port number so that FD connections get to the right place
    if ((::bind(serverSocketFd, (struct sockaddr *) &serverAddress, sizeof(serverAddress))) < 0) {
        throw SocketException(
                "Binding fileDescriptor failed.\nThe port may be already taken or it is not a valid port for your system.");
    }

    addressSize = sizeof(serverAddress);
}

/**
 * Accept a client connection to the socket previously created.
 * The process will stay idle (waiting) until a client connection is made.
 */
netry::Socket netry::ServerSocket::accept() throw(SocketException) {
    // Listen for socket connections and limit the queue of incoming connections
    if (listen(serverSocketFd, 1) < 0) {
        throw SocketException("Could not listen for connections");
    }

    int clientSocket = 0;

    // Waits for a client
    clientSocket = ::accept(serverSocketFd, (struct sockaddr *) &serverAddress, &addressSize);

    // A client has connected
    // Check if the connection is valid
    if (clientSocket < 0) {
        throw SocketException("Error on accepting client connection");
    }

    return Socket(clientSocket);
}

/**
 * Closes the File Descriptor (FD) of the server
 * Wait to close until all data is transmitted.
 */
void netry::ServerSocket::close() {
    ::close(serverSocketFd);
}


