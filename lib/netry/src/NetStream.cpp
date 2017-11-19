/**
 * Netry is a high level networking implementation of The Single UNIX Specification, Version 2.
 * @see: http://pubs.opengroup.org/onlinepubs/7908799/xnsix.html
 */
//
// Created by mz on 22/10/17.
//

#include "../include/NetStream.h"

netry::NetStream::NetStream() = default;

/**
 * Constructor that initiates the File Descriptor
 */
netry::NetStream::NetStream(const netry::Socket &socket) : socket(socket) {}

/**
 * Write bytes to a socket endpoint
 * @param bytes
 * @param size
 */
void netry::NetStream::writeBytes(const char *bytes, size_t size) const {

    // TODO: check if connection is valid before transaction and throw an exception otherwise

    // Sends the number of bytes that will be sent
    send(socket.getFileDescriptor(), &size, sizeof(size_t), 0);
    // Sends the bytes from buffer
    send(socket.getFileDescriptor(), bytes, size, 0);
}

/**
 * Receive bytes through socket
 *
 * @param buffer: where the bytes will be stored
 * @return the number of bytes read
 */
ssize_t netry::NetStream::readBytes(char buffer[]) const {

    // TODO: check if connection is valid before transaction and throw an exception otherwise

    size_t bytesReceived = 0;
    // Receives the number of bytes that will come from the buffer
    recv(socket.getFileDescriptor(), &bytesReceived, sizeof(size_t), 0);
    // Receives the data from buffer according to the number of bytes
    return recv(socket.getFileDescriptor(), buffer, bytesReceived, 0);
}

/**
 * Writes a string to a socket endpoint
 */
void netry::NetStream::writeString(const std::string &message) const {

    // TODO: check if connection is valid before transaction and throw an exception otherwise

    // Converts string to const char *
    const char *c = message.c_str();
    // Gets the size of the string
    const size_t size = message.length() + kStringEndLength;
    // Sends the number of bytes of the string
    send(socket.getFileDescriptor(), &size, sizeof(size_t), 0);
    // Sends the string
    send(socket.getFileDescriptor(), c, size, 0);
}

/**
 * Receive a string from a socket stream
 *
 * @return the received string
 */
std::string netry::NetStream::readString() const {

    // TODO: check if connection is valid before transaction and throw an exception otherwise

    size_t bytesReceived = 0;
    // Receives the number of bytes of the string
    recv(socket.getFileDescriptor(), &bytesReceived, sizeof(size_t), 0);
    char buffer[bytesReceived];
    // Receives the string
    recv(socket.getFileDescriptor(), buffer, bytesReceived, 0);
    return std::string(buffer, bytesReceived - 1);
}

void netry::NetStream::writeInt(int data) const {

    // TODO: check if connection is valid before transaction and throw an exception otherwise

    send(socket.getFileDescriptor(), &data, sizeof(data), 0);
}

int netry::NetStream::readInt() const {

    // TODO: check if connection is valid before transaction and throw an exception otherwise

    int data;
    recv(socket.getFileDescriptor(), &data, sizeof(int), 0);
    return data;
}

const netry::Socket &netry::NetStream::getSocket() const {
    return socket;
}

void netry::NetStream::setSocket(const netry::Socket &socket) {
    NetStream::socket = socket;
}
