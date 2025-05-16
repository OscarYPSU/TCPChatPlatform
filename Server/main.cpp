#include <winsock2.h>
#include <iostream>

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(serverSocket, 1);

    std::cout << "Server started. Waiting for one client...\n";

    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    std::cout << "Client connected!\n";

    char buffer[1024];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break; // error occured

        buffer[bytesReceived] = '\0';
        std::cout << "Client says: " << buffer << "\n";

        send(clientSocket, buffer, bytesReceived, 0);
    }
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}