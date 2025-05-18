#include<winsock2.h>
#include<iostream>
#include "testUI.h"
#include "main.h"

// Function for sending message
std::string main::sendMessage(SOCKET sock, const std::string& message) {
    char buffer[1024];
    send(sock, message.c_str(), message.size(), 0);
    int bytesReceieved = recv(sock, buffer, sizeof(buffer), 0);
    buffer[bytesReceieved] = '\0';
    std::cout << "Server echoed: " << buffer << "\n";
    return std::string(buffer);
}

int main(int argc, char *argv[]) {
    WSADATA wsa; // The WSADATA structure that will get filled with implementation info
    WSAStartup(MAKEWORD(2, 2), &wsa); //  initializes the winsock library

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    // The address at which the IPV4 server resides at AKA port 12345, host 127.0.0.1
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost


    // Connects the client socket to the server address
    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
    std::cout <<"Successfuly connected to server!\n";

    QApplication app(argc, argv);
    TestUI window(sock);
    window.show();

    return app.exec();
}
