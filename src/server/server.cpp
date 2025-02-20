#include "distributed_trace.h"
#include <iostream>
#include <string>

#define PORT 8080

int main() {
    Socket socket(AF_INET, SOCK_STREAM);
    socket.bind(PORT);

    socket.listen(3);

    std::cout << "Server is listening on port " << PORT << std::endl;

    Socket new_socket = socket.accept();

    std::string buffer;
    new_socket.receive(buffer, 1024);

    std::cout << "Received message: " << buffer << std::endl;

    std::string response = "Hello from server!";
    new_socket.send(response);
    std::cout << "Response sent" << std::endl;

    return 0;
}

