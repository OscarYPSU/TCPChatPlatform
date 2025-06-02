//
// Created by oskhy on 5/25/2025.
//

#include "sql.h"
#include <libpq-fe.h>
#include<iostream>
#include <vector>


int registerUser(PGconn *conn, std::string &username, std::string &password) {
    std::string query = "INSERT INTO users(username, password) VALUES('" + username + "', '" + password + "');";
    PGresult *result = PQexec(conn, query.c_str());

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Creating user failed ERROR CODE: " << PQerrorMessage(conn) << "\n";
        PQclear(result);
        return 1;
    } else {
        std::cout << "Insert successful." << std::endl;
        PQclear(result);
        return 0;
    }
}

int loginUser(PGconn *conn, std::string &username, std::string &password) {
    std::string query = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "';";
    PGresult *result = PQexec(conn, query.c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(result);
        return 1;
    }
    int rows = PQntuples(result);
    if (rows == 0) {
        std::cout << "No user found with the credentials\n";
        PQclear(result);
        return 1;
    } else {
        std::cout << "ID: " << PQgetvalue(result, 0, 0) << ", username: " << PQgetvalue(result, 0, 1) << ", password: " << PQgetvalue(result, 0, 2) << "\n";
    }
    PQclear(result);
    return 0;
}

std::vector<std::string> getUsernames(PGconn *conn) {
    std::string query = "SELECT username FROM users";
    std::vector<std::string> listUsernames;
    PGresult *result = PQexec(conn, query.c_str());
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(result);
    }

    int rows = PQntuples(result);
    if (rows == 0) {
        std::cerr << "No user is found\n";
        PQclear(result);
    } else {
        for (int i = 0; i < rows; ++i) {
            std::cout << "ADDING USERNAME TO LIST: " << PQgetvalue(result, i, 0) << "\n"; // logging
            listUsernames.push_back(PQgetvalue(result, i, 0));
        }
    }

    return listUsernames;
}

