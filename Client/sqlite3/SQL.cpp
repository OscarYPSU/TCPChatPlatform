#include <iostream>
#include "sqlite3.h"
#include "SQL.h"

void SQL::registerUser(sqlite3* db, std::string &username, std::string &password){
    std::string query = "INSERT INTO users (name, password) VALUES ('" + username + "', '" + password + "');";
    char *errorMessage = nullptr;

    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error" << errorMessage << "\n";
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Successfully created user " << username;
    }

}

void SQL::loginUser(sqlite3 *db, std::string &username, std::string &password) {
    std::string query = "SELECT * FROM users WHERE password = '" + password + "' AND name  = '" + username + "';";
    char *errorMessage = nullptr;

    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL ERROR IN GETTING USER INFORMATION, ERROR CODE: " << rc << "\n";
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Successfully found user.\n";
    }

}

