#include "distributed_trace.h"
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <chrono>

#define PORT 8080

int main() {
    Socket socket(AF_INET, SOCK_STREAM);
    while (socket.connect("192.168.0.100", PORT) != 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    // Send a message to the server
    std::string message = "Hello from client!";
    socket.send(message);
    std::cout << "Message sent" << std::endl;

    // Read server's response
    std::string buffer;
    socket.receive(buffer, 1024);
    std::cout << "Server response: " << buffer << std::endl;

    return 0;
}

