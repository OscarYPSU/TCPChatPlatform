//
// Created by oskhy on 5/25/2025.
//

#include "sql.h"
#include <libpq-fe.h>
#include<iostream>


int registerUser(PGconn *conn, std::string &username, std::string &password) {
    std::string query = "INSERT INTO users(username, password) VALUES('" + username + "', '" + password + "');";
    PGresult *result = PQexec(conn, query.c_str());

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Creating user failed ERROR CODE: " << PQerrorMessage(conn) << "\n";
        PQclear(result);
        PQfinish(conn);
        return 1;
    } else {
        std::cout << "Insert successful." << std::endl;
        PQclear(result);
        PQfinish(conn);
        return 0;
    }
}