//
// Created by oskhy on 5/20/2025.
//

#include "frontPage.h"
#include "../globalResource/globals.h"
#include "../sqlQueries/sql.h"
#include <libpq-fe.h>

void frontPage::registerButtonClicked() {
    // gets username and password form user input
    QString username = newUI.usernameUserInput->toPlainText();
    QString password = newUI.passwordUserInput->text();

    // process it to std::string data
    std::string usernameString = username.toStdString();
    std::string passwordString = username.toStdString();

    // executes the query
    registerUser(conn, usernameString, passwordString);
}

void frontPage::loginButtonClicked() {
    // gets username and password form user input
    QString username = newUI.usernameUserInput->toPlainText();
    QString password = newUI.passwordUserInput->text();

    // process it to std::string data
    std::string usernameString = username.toStdString();
    std::string passwordString = password.toStdString();

    // sets the global variable of the logged user's name
    ::username = usernameString;

    // executes the query
    if (!loginUser(conn, usernameString, passwordString)) { // if returns 0 meaning success
        newUI.StackedWidget->setCurrentIndex(1);
    }
}

frontPage::frontPage(PGconn *conn, QWidget *parent):QMainWindow(parent), conn(conn){
    newUI.setupUi(this);
    connect(newUI.registerButton, &QPushButton::clicked, this, &frontPage::registerButtonClicked);
    connect(newUI.loginButton, &QPushButton::clicked, this, &frontPage::loginButtonClicked);
}
