//
// Created by oskhy on 5/17/2025.
//
#include <thread>
#include "testUI.h"
#include "../main.h"
#include<iostream>

void TestUI::updateReceivedMessage() {
    while (true) {
        std::string message;

        {
            std::lock_guard<std::mutex> lock(messagesMutex);
            // if the vector is not empty
            if (!receivedMessages.empty()) {
                // store the first data and erase it from the vector
                message = receivedMessages.front();
                receivedMessages.erase(receivedMessages.begin());
            } else {
                // stops thread for tiny bit
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                continue;
            }
        }

        // This MUST run on the QT GUI thread
        QMetaObject::invokeMethod(this, [this, message]() {
            QString qMessage = QString::fromStdString(message);
            ui.displayMessageText->appendPlainText("Them: " + qMessage);
        });
    }
}

void TestUI::onSendButtonClicked() {
    // Gets Qstring from user input
    QString inputText = ui.userMessageTextInput->toPlainText();
    // converts the input text from Qstring to string class
    std::string inputStdString = inputText.toStdString();
    main.sendMessage(clientsock, inputStdString); // sends the message over


    // Clears the user input
    ui.userMessageTextInput->clear();

    // Adds text chat history
    ui.displayMessageText->appendPlainText("You: " + inputText);

}

TestUI::TestUI(SOCKET sock, QWidget *parent):QMainWindow(parent), clientsock(sock){
    // starts the thread for updating the QT gui when receiving messages
    ui.setupUi(this);
    connect(ui.sendButton, &QPushButton::clicked, this, &TestUI::onSendButtonClicked);
    std::thread([this]() { updateReceivedMessage(); }).detach();
}
