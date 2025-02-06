#include <cstdint>
#include <netinet/in.h>
#include <string>
#include <vector>

using ip_t = std::string;
using port_t = uint16_t;
using af_t = int;
using socktype_t = int;

class Socket {
private:
    int sockfd;
    sockaddr_in address;

public:
    Socket() : sockfd(-1) {}
    void initialize(ip_t host, port_t port);
    void create(af_t family, socktype_t type);
    void bind();
    void listen(int backlog);
    int accept();
    int connect();
    int send(const std::vector<char>& data);
    std::vector<char> receive(int buffer_size);
    void close();
    ~Socket();
};
