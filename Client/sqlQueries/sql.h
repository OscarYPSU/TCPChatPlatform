//
// Created by oskhy on 5/25/2025.
//

#ifndef SQL_H
#define SQL_H

#include <iostream>
#include <libpq-fe.h>
#pragma once


int registerUser(PGconn *conn, std::string &username, std::string &password);
int loginUser(PGconn *conn, std::string &username, std::string &password);


#endif //SQL_H
