#include <cstddef>
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
    std::vector<char> sbuf;

    Socket(int sockfd): sockfd(sockfd) {}
public:
    Socket(af_t family, socktype_t type);
    int bind(port_t port);
    int listen(int backlog);
    Socket accept();
    int connect(ip_t target, port_t port);
    int send(const std::string s);
    int send(const std::vector<std::byte>& buffer, int send_size);
    int receive(std::string& s, int recv_size);
    int receive(std::vector<std::byte>& buffer, int recv_size);
    void close();
    ~Socket();
};
