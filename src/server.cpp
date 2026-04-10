#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "store.h"
#include "thread_pool.h"

#define PORT 8080
#define BUFFER_SIZE 4096

KeyValueStore store;
ThreadPool pool(4);

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_fd, buffer, BUFFER_SIZE - 1);
    
    std::string request(buffer);
    std::istringstream iss(request);
    std::string command, key, value;
    iss >> command >> key;
    
    std::string response;
    
    if (command == "SET") {
        iss >> value;
        store.set(key, value);
        response = "OK\n";
    } 
    else if (command == "GET") {
        response = store.get(key) + "\n";
    }
    else if (command == "DELETE") {
        bool deleted = store.del(key);
        response = deleted ? "DELETED\n" : "NOT_FOUND\n";
    }else if (command == "COUNT") {
        response = std::to_string(store.count()) + "\n";
    }
    else {
        response = "ERROR: Unknown command\n";
    }
    
    send(client_fd, response.c_str(), response.length(), 0);
    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 10);
    
    std::cout << "Server listening on port " << PORT << std::endl;
    
    while (true) {
        client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        pool.enqueue([client_fd] { handle_client(client_fd); });
    }
    
    close(server_fd);
    return 0;
}