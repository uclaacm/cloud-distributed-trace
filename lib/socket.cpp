#include "socket.h"
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>
#include <unistd.h>
#include <vector>

void Socket::initialize(ip_t host, port_t port) {
    std::memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &address.sin_addr) <= 0) {
        throw std::invalid_argument("Invalid IP address.");
    }
}

void Socket::create(af_t family, socktype_t type) {
    sockfd = socket(family, type, 0);
    if (sockfd < 0) {
        throw std::runtime_error("Failed to create socket.");
    }
}

void Socket::bind() {
    if (::bind(sockfd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
        throw std::runtime_error("Failed to bind socket.");
    }
}

void Socket::listen(int backlog) {
    if (::listen(sockfd, backlog) < 0) {
        throw std::runtime_error("Failed to listen on socket.");
    }
}

int Socket::accept() {
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sock = ::accept(sockfd, reinterpret_cast<struct sockaddr*>(&client_addr), &client_len);

    if (client_sock < 0) {
        throw std::runtime_error("Failed to accept connection.");
    }
    return client_sock;
}

int Socket::connect() {
    if (::connect(sockfd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
        perror("Connection failed");
        return -1;
    }
    return 0;
}

int Socket::send(const std::vector<char> &data) {
    ssize_t bytes_sent = ::send(sockfd, data.data(), data.size(), 0);
    if (bytes_sent < 0) {
        throw std::runtime_error("Failed to send data.");
    }
    return static_cast<int>(bytes_sent);
}

std::vector<char> Socket::receive(int buffer_size) {
    std::vector<char> buffer(buffer_size);
    ssize_t bytes_received = recv(sockfd, buffer.data(), buffer_size, 0);

    if (bytes_received < 0) {
        throw std::runtime_error("Failed to receive data.");
    }
    buffer.resize(bytes_received); // Trim buffer to actual data size
    return buffer;
}

void Socket::close() {
    if (sockfd >= 0) {
        ::close(sockfd);
        sockfd = -1;
    }
}

Socket::~Socket() {
    close();
}
