//
// Created by oskhy on 5/20/2025.
//

#include "frontPage.h"
#include "../globalResource/globals.h"
#include "../sqlQueries/sql.h"
#include "../session/session.h"
#include <libpq-fe.h>
#include <mutex>
#include <thread>

void frontPage::registerButtonClicked() {
    // gets username and password form user input
    QString username = newUI.usernameUserInput->toPlainText();
    QString password = newUI.passwordUserInput->text();

    // process it to std::string data
    std::string usernameString = username.toStdString();
    std::string passwordString = username.toStdString();

    // executes the query
    registerUser(conn, usernameString, passwordString);

    // hides wrong credential label if user creates a new acc after inputting wrong info
    newUI.wrongCrfedentialsLabel->hide();
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
        // stores the username into singleton class
        session::getInstance().login(usernameString);
        main.sendMessage(clientsock, "LOGGEDIN# = " + session::getInstance().getUsername());
        loadPrivateMessageComboBox(); // loads up combo box after user logs in
    } else {
        newUI.wrongCrfedentialsLabel->show();
    }

}

void frontPage::updateReceivedMessage() {
    while (true) {
        std::string message;
        std::string rawMessage;
        std::string userTalking;
        std::string processedMessage;

        {
            std::lock_guard<std::mutex> lock(messagesMutex);
            // if the vector is not empty
            if (!receivedMessages.empty()) {
                // store the first data and erase it from the vector
                rawMessage = receivedMessages.front();
                receivedMessages.erase(receivedMessages.begin());


                size_t firstEndingIndex = rawMessage.find(";");
                size_t secondEndingIndex = rawMessage.find(";", firstEndingIndex + 1);

                // finds the user talking
                size_t indexUser = rawMessage.find("USER: ") + 6;
                userTalking = rawMessage.substr(indexUser, firstEndingIndex - indexUser);
                std::cout << "USER SENDING MESSAGE: " << userTalking << "\n"; //logging

                // finds the message
                size_t messageIndex = rawMessage.find("MESSAGE: ") + 9;
                message = rawMessage.substr(messageIndex, secondEndingIndex - messageIndex);
                std::cout << "SENDING MESSAGE: " << message << "\n"; //logging

                processedMessage = userTalking + ": " + message;

            } else {
                // stops thread for tiny bit
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                continue;
            }
        }

        // This MUST run on the QT GUI thread
        QMetaObject::invokeMethod(this, [this, processedMessage]() {
            QString qMessage = QString::fromStdString(processedMessage);
            newUI.displayMessageText->appendPlainText(qMessage);
        });
    }
}

void frontPage::onSendButtonClicked() {
    // Gets Qstring from user input
    QString inputText = newUI.userMessageTextInput->toPlainText();
    // converts the input text from Qstring to string class
    std::string inputStdString = inputText.toStdString();
    // grabs who the message is going to be sent to
    std::string receiver = newUI.selectPrivateMessageComboBox->currentText().toStdString();
    std::cout << "RECEIVER : " << receiver << "\n"; // logging

    // loads the input text with necessary information to send to server
    inputStdString = "USER: " + session::getInstance().getUsername() + "; MESSAGE: " + inputStdString + ";RECEIVER: " + receiver + ";";

    std::cout << "INPUT STRING: " << inputStdString << "\n"; // logging

    main.sendMessage(clientsock, inputStdString); // sends the message over


    // Clears the user input
    newUI.userMessageTextInput->clear();

    // Adds text chat history
    newUI.displayMessageText->appendPlainText("You: " + inputText);

}

void frontPage::loadPrivateMessageComboBox() {
    std::vector<std::string> usernameList = getUsernames(conn); // gets the usernames lists
    // fills all existing username into combo box
    for (std::string username : usernameList) {
        newUI.selectPrivateMessageComboBox->addItem(QString::fromStdString(username));
    }
}

void frontPage::closeEvent(QCloseEvent *event)
{
    event->ignore(); // Allows the window to close

}

frontPage::frontPage(SOCKET sock, PGconn *conn, QWidget *parent):QMainWindow(parent), clientsock(sock), conn(conn){
    newUI.setupUi(this);
    connect(newUI.registerButton, &QPushButton::clicked, this, &frontPage::registerButtonClicked);
    connect(newUI.loginButton, &QPushButton::clicked, this, &frontPage::loginButtonClicked);
    connect(newUI.sendButton, &QPushButton::clicked, this, &frontPage::onSendButtonClicked);

    // creates a thread that constantly updates the message box
    std::thread([this]() { updateReceivedMessage(); }).detach();

    // Hides the wrong user credential text
    newUI.wrongCrfedentialsLabel->hide();
}
