#include <cstddef>
#include <cstdint>
#include <netinet/in.h>
#include <string>
#include <vector>

using ip_t = std::string;      // IP address as a string (e.g., "127.0.0.1")
using port_t = uint16_t;       // Port number (e.g., 8080)
using af_t = int;              // Address family (e.g., AF_INET)
using socktype_t = int;        // Socket type (e.g., SOCK_STREAM)

class Socket {
private:
    int sockfd;                // Socket file descriptor
    sockaddr_in address;       // Socket address structure
    std::vector<char> sbuf;    // Send buffer

    Socket(int sockfd): sockfd(sockfd) {} // Private constructor for accepted sockets
public:
    // Constructor: Creates a socket with the specified address family and type.
    Socket(af_t family, socktype_t type);

    // Binds the socket to the specified port.
    int bind(port_t port);

    // Puts the socket in a listening state with the specified backlog queue size.
    int listen(int backlog);

    // Accepts an incoming connection and returns a new Socket for communication.
    Socket accept();

    // Connects the socket to the specified target IP and port.
    int connect(ip_t target, port_t port);

    // Sends a string over the socket and returns the number of bytes sent.
    int send(const std::string s);

    // Sends a binary buffer over the socket and returns the number of bytes sent.
    int send(const std::vector<std::byte>& buffer, int send_size);

    // Receives data into a string and returns the number of bytes received.
    int receive(std::string& s, int recv_size);

    // Receives data into a binary buffer and returns the number of bytes received.
    int receive(std::vector<std::byte>& buffer, int recv_size);

    // Closes the socket and releases resources.
    void close();

    // Destructor: Ensures the socket is closed when the object is destroyed.
    ~Socket();
};