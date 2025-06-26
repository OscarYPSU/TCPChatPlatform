//
// Created by oskhy on 5/25/2025.
//

#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <libpq-fe.h>
#include <vector>
#pragma once


int registerUser(PGconn *conn, std::string &username, std::string &password);
int loginUser(PGconn *conn, std::string &username, std::string &password);
std::vector<std::string> getUsernames(PGconn *conn);
std::vector<std::vector<std::string>> getMessageHistory(PGconn *conn, std::string sender);


#endif //SQL_H
