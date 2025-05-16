#include <winsock2.h>
#include <iostream>

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

    // Starst the server socket to wait for a client connection
    std::cout << "Server started. Waiting for one client...\n";
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    std::cout << "Client connected!\n";

    // Data to store message
    char buffer[1024];
    while (true) {

        // Whatever is sent through the client socket is saved to buffer data structure and saved to bytresReceived data
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break; // error occured

        // Gets rid of garbage information
        buffer[bytesReceived] = '\0';
        std::cout << "Client says: " << buffer << "\n";

        // Sends the message back to the client socket
        send(clientSocket, buffer, bytesReceived, 0);
    }
    // Closes both socket and cleans up the api
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}