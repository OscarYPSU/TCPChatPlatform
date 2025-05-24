#include <winsock2.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::vector<SOCKET> clients;
std::mutex clientsMutex;

void handleClients(SOCKET clientSocket) {
    char buffer[1024];

    while (true) {
        // Whatever is sent through the client socket is saved to buffer data structure and saved to bytresReceived data
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break; // error occured

        // Gets rid of garbage information
        buffer[bytesReceived] = '\0';
        std::cout << "Client says: " << buffer << "\n";

        std::lock_guard<std::mutex> lock(clientsMutex);
        for (SOCKET client: clients) {
            if (client != clientSocket) {
                send(client, buffer, bytesReceived, 0);
            }
        }
    }
}

int main() {
    // starts WSADATA api
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Creates a IPV4, organized stream socket with default protocol
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Sets the IPV4 server address at port 12345, open to any IP address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Binds the socket to this address
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    //  initiliazes the server socket for 1 client
    listen(serverSocket, 1);

    // start  the server socket to wait for a client connection
    std::cout << "Server started. Waiting for clients...\n";

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr
            , nullptr);
        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients.push_back(clientSocket);
        }
        std::thread(handleClients, clientSocket).detach(); // starts the handling of client in a thread
        std::cout << "Client connected\n";
    }
    WSACleanup();
    return 0;
}