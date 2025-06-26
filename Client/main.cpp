#include<winsock2.h>
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<chrono>
#include <libpq-fe.h>
#include "main.h"
#include "UI/frontPage.h"
#include "sqlQueries/sql.h"
#include "session/session.h"


std::vector<std::string> receivedMessages;
std::mutex messagesMutex;

// Function for sending message
void mainFunction::sendMessage(SOCKET sock, const std::string& message) {
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
    PGconn *conn = PQconnectdb("host=localhost port=1234 dbname=TSPChatApplication user=postgres password=Oscarsgyang123");
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed ERROR CODE: " << PQerrorMessage(conn) << "\n";
        PQfinish(conn);
        return 1;
    } else {
        std::cout << "Successfully connected to database\n";
    }

    WSADATA wsa; // The WSADATA structure that will get filled with implementation info
    WSAStartup(MAKEWORD(2, 2), &wsa); //  initializes the winsock library

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    // The address at which the IPV4 server resides at AKA port 12345, host 127.0.0.1
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost


    // Connects the client socket to the server address and sends the server user's username
    int result = connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
    // attempts to reconnect to server if there is no server found at current moment
    while (result == SOCKET_ERROR) {
        std::cerr << "Error in connecting to server | LINE 63 main.cpp\n";
        result = connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
        std::cout << "Attempting to connect to server\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    }

    std::cout <<"Successfuly connected to server!\n";

    std::thread(receiveMessage, sock).detach();

    QApplication app(argc, argv);
    frontPage window2(sock, conn);
    window2.show();

    return app.exec();
}
