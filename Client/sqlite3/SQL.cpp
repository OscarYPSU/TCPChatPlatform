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

    sqlite3_stmt *statement;
    int rc1;
    std::string query1 = "SELECT * FROM users WHERE name = ? AND password = ?;";

    if (sqlite3_prepare_v2(db, query1.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(statement) == SQLITE_ROW) {

    }
}

