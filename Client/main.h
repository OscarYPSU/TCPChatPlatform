//
// Created by oskhy on 5/18/2025.
//

#ifndef MAIN_H
#define MAIN_H

#include <winsock2.h>
#include <iostream>
#include <vector>
#include <mutex>

extern std::vector<std::string> receivedMessages;
extern std::mutex messagesMutex;

class main {
public:
    void sendMessage(SOCKET sock, const std::string& message);
};

#endif //MAIN_H
