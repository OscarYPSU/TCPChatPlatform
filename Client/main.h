//
// Created by oskhy on 5/18/2025.
//

#ifndef MAIN_H
#define MAIN_H

#include <winsock2.h>
#include <iostream>

class main {
public:
    std::string sendMessage(SOCKET sock, const std::string& message);

};

#endif //MAIN_H
