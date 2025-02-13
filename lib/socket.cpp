#include "socket.h"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Socket::Socket(af_t family, socktype_t type) {
    sockfd = socket(family, type, 0);
    if (sockfd < 0)
        throw std::runtime_error("Failed to create socket.");
    address.sin_family = family;
    address.sin_addr.s_addr = INADDR_ANY;
}

int Socket::bind(port_t port) {
    address.sin_port = htons(port);
    return ::bind(sockfd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address));
}

int Socket::listen(int backlog) {
    return ::listen(sockfd, backlog);
}

Socket Socket::accept() {
    socklen_t client_len = sizeof(address);
    int client_sock = ::accept(sockfd, reinterpret_cast<struct sockaddr*>(&address), &client_len);
    if (client_sock < 0) {
        throw std::runtime_error("Failed to accept connection.");
    }
    return Socket(client_sock);
}

int Socket::connect(ip_t target, port_t port) {
    address.sin_port = htons(port);
    if (inet_pton(AF_INET, "192.168.0.100", &address.sin_addr) <= 0) {
        return -1;
    }
    if (::connect(sockfd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
        return -1;
    }
    return 0;
}

int Socket::send(const std::string s) {
    ssize_t bytes_sent = ::send(sockfd, s.c_str(), s.length(), 0);
    return static_cast<int>(bytes_sent);
}

int Socket::send(const std::vector<std::byte>& buffer, int send_size) {
    if (buffer.size() < send_size)
        return -1;
    ssize_t bytes_sent = ::send(sockfd, buffer.data(), send_size, 0);
    return static_cast<int>(bytes_sent);
}

int Socket::receive(std::string& s, int recv_size) {
    sbuf.resize(recv_size);

    ssize_t bytes_received = recv(sockfd, &sbuf[0], recv_size, 0);

    if (bytes_received >= 0)
        s = std::string(sbuf.data());

    return bytes_received;
}

int Socket::receive(std::vector<std::byte>& buffer, int recv_size) {
    buffer.resize(recv_size);
    ssize_t bytes_received = recv(sockfd, &buffer[0], recv_size, 0);
    return bytes_received;
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
