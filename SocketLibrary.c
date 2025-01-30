#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using ip_t = std::string;
using port_t = uint16_t;
using af_t = int;          
using socktype_t = int;

class SocketLibrary {
private:
    int sockfd;
    sockaddr_in address;

public:
    SocketLibrary() : sockfd(-1) {}

    void initialize(const ip_t &host, port_t port) {
        std::memset(&address, 0, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_port = htons(port);

        if (inet_pton(AF_INET, host.c_str(), &address.sin_addr) <= 0) {
            throw std::invalid_argument("Invalid IP address.");
        }
    }

    void create_socket(af_t family, socktype_t type) {
        sockfd = socket(family, type, 0);
        if (sockfd < 0) {
            throw std::runtime_error("Failed to create socket.");
        }
    }

    void bind_socket() {
        if (bind(sockfd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
            throw std::runtime_error("Failed to bind socket.");
        }
    }

    void listen_socket(int backlog) {
        if (listen(sockfd, backlog) < 0) {
            throw std::runtime_error("Failed to listen on socket.");
        }
    }

    int accept_connection() {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(sockfd, reinterpret_cast<struct sockaddr*>(&client_addr), &client_len);

        if (client_sock < 0) {
            throw std::runtime_error("Failed to accept connection.");
        }
        return client_sock;
    }

    int connect_socket() {
        if (connect(sockfd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
            perror("Connection failed");
            return -1;
        }
        return 0;
    }

    int send_data(const std::vector<char> &data) {
        ssize_t bytes_sent = send(sockfd, data.data(), data.size(), 0);
        if (bytes_sent < 0) {
            throw std::runtime_error("Failed to send data.");
        }
        return static_cast<int>(bytes_sent);
    }

    std::vector<char> receive_data(int buffer_size) {
        std::vector<char> buffer(buffer_size);
        ssize_t bytes_received = recv(sockfd, buffer.data(), buffer_size, 0);

        if (bytes_received < 0) {
            throw std::runtime_error("Failed to receive data.");
        }
        buffer.resize(bytes_received); // Trim buffer to actual data size
        return buffer;
    }

    void close_socket() {
        if (sockfd >= 0) {
            close(sockfd);
            sockfd = -1;
        }
    }

    ~SocketLibrary() {
        close_socket();
    }
};