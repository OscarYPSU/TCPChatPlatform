//
// Created by oskhy on 5/28/2025.
//

#ifndef SOURCE_H
#define SOURCE_H

#include <iostream>
#pragma once

class session {
private:
    std::string username;
    bool loggedIn = false;
    session(){}

public:
    // stops session singleton class from being copied ensuring its SINGLE
    session(const session&) = delete;
    session &operator=(const session&) = delete;

    static session &getInstance() {
        static session instance;
        return instance;
    }

    void login(const std::string& user) {
        username = user;
        loggedIn = true;

        // logging
        std::cout << username << " logged in\n";
    }

    void logout() {
        username.clear();
        loggedIn = false;
    }

    std::string getUsername() const { return username; }
    bool isLoggedIn() const { return loggedIn; }
};

#endif //SOURCE_H
