#include<winsock2.h>
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include "UI/testUI.h"
#include "main.h"
#include "UI/frontPage.h"
#include "sqlite3/sqlite3.h"

std::vector<std::string> receivedMessages;
std::mutex messagesMutex;

// Function for sending message
void main::sendMessage(SOCKET sock, const std::string& message) {
    send(sock, message.c_str(), message.size(), 0);
}

void receiveMessage(SOCKET sock) {
    char buffer[1024];
    while (true) {
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;
        buffer[bytesReceived] = '\0';
        std::cout << ">> " << buffer << "\n";
        std::string message(buffer); // converts char to string to be added to vector
        // lock the vector before modifying it
        {
            std::lock_guard<std::mutex> lock(messagesMutex);
            receivedMessages.push_back(message);
        }
    }
}

int main(int argc, char *argv[]) {
    // connects to the database
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        std::cerr << "Can't open DB: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Opened DB successfully.\n";
    }

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

    std::thread(receiveMessage, sock).detach();

    QApplication app(argc, argv);
    TestUI window(sock);
    frontPage window2(db);
    window2.show();

    return app.exec();


    /* for new UI
    QApplication app(argc, argv);
    NewPage window;
    window.show();
    return app.exec();
    */
}
