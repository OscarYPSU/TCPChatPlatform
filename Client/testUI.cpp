//
// Created by oskhy on 5/17/2025.
//
#include "testUI.h"
#include "main.h"

TestUI::TestUI(SOCKET sock, QWidget *parent):QMainWindow(parent), clientsock(sock){
    ui.setupUi(this);

    connect(ui.sendButton, &QPushButton::clicked, this, &TestUI::onSendButtonClicked);
}

void TestUI::onSendButtonClicked() {
    // Gets Qstring from user input
    QString inputText = ui.userMessageTextInput->toPlainText();
    // converts the input text from Qstring to string class
    std::string inputStdString = inputText.toStdString();
    // What the server sent back and converted to Qstring to be shown
    QString echoedBack = QString::fromStdString(client.sendMessage(clientsock, inputStdString));

    // Clears the user input
    ui.userMessageTextInput->clear();

    // Adds text chat history
    ui.displayMessageText->appendPlainText("You: " + inputText);
    ui.displayMessageText->appendPlainText("Server: " + echoedBack);
}