//
// Created by oskhy on 5/21/2025.
//

#ifndef TESTSQL_H
#define TESTSQL_H

#include<iostream>

class sql {
    public:
        void registerUser(sqlite3 *db, std::string &username, std::string &password);
        void loginUser(sqlite3 *db, std::string &username, std::string &password);
};

#endif //TESTSQL_H
