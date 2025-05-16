#include<winsock2.h>
#include<iostream>

void sendMessage(SOCKET sock, const std::string& message) {
    char buffer[1024];
    send(sock, message.c_str(), message.size(), 0);
    int bytesReceieved = recv(sock, buffer, sizeof(buffer), 0);
    buffer[bytesReceieved] = '\0';
    std::cout << "Server echoed: " << buffer << "\n";
}

int main() {
    WSADATA wsa; // The WSADATA structure that will get filled with implementation info
    WSAStartup(MAKEWORD(2, 2), &wsa); //  initializes the winsock library

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost

    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
    std::cout <<"Successfuly connected to server!\n";

    std::string message;
    char buffer[1024];

    sendMessage(sock, "testing");
    /*
    while (true) {
        std::getline(std::cin, message);
        send(sock, message.c_str(), message.size(), 0);

        int bytes = recv(sock, buffer, sizeof(buffer), 0);
        buffer[bytes] = '\0';
        std::cout << "Server echoed: " << buffer << "\n";
    }
    */

    closesocket(sock);
    WSACleanup();
    return 0;
}