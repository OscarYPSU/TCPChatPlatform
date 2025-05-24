//
// Created by oskhy on 5/20/2025.
//

#include "frontPage.h"
#include "../sqlite3/sqlite3.h"
#include "../sqlite3/SQL.h"

void frontPage::registerButtonClicked() {
    // gets username and password form user input
    QString username = newUI.usernameUserInput->toPlainText();
    QString password = newUI.passwordUserInput->text();

    // process it to std::string data
    std::string usernameString = username.toStdString();
    std::string passwordString = username.toStdString();

    // executes the query
    sql.registerUser(db, usernameString, passwordString);
}

void frontPage::loginButtonClicked() {
    // gets username and password form user input
    QString username = newUI.usernameUserInput->toPlainText();
    QString password = newUI.passwordUserInput->text();

    // process it to std::string data
    std::string usernameString = username.toStdString();
    std::string passwordString = username.toStdString();

    // executes the query
    sql.loginUser(db, usernameString, passwordString);
}

frontPage::frontPage(sqlite3 *db, QWidget *parent):QMainWindow(parent), db(db) {
    newUI.setupUi(this);
    connect(newUI.registerButton, &QPushButton::clicked, this, &frontPage::registerButtonClicked);
    connect(newUI.loginButton, &QPushButton::clicked, this, &frontPage::loginButtonClicked);
}
