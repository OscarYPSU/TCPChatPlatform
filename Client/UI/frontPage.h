//
// Created by oskhy on 5/20/2025.
//

#ifndef NEWPAGE_H
#define NEWPAGE_H

#include <QMainWindow>
#include "ui_frontPage.h"
#include "../main.h"
#include "../sqlQueries/sql.h"
#include <libpq-fe.h>
#include <winsock2.h>
#pragma once

class frontPage: public QMainWindow {
    Q_OBJECT

    public:
        explicit frontPage(SOCKET sock, PGconn *conn, QWidget *parent = nullptr);


    private slots:
        void registerButtonClicked();
        void loginButtonClicked();
        void updateReceivedMessage();
        void onSendButtonClicked();

    private:
        Ui::frontPage newUI;
        PGconn *conn;
        mainFunction main;
        SOCKET clientsock;
};

#endif //NEWPAGE_H
