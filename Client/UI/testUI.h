#ifndef TESTUI_H
#define TESTUI_H

#include "ui_testUI.h"  // <- auto-generated from testUI.ui
#include "../main.h"
#include<winsock2.h>

class TestUI: public QMainWindow {
    Q_OBJECT
    public:
        explicit TestUI(SOCKET sock, QWidget *parent = nullptr);

    private slots:
        void onSendButtonClicked(); // Slot (function) to handle the click
        void updateReceivedMessage();

    private:
        Ui::TestUI ui;
        main main;
        SOCKET clientsock;
};

#endif // TESTUI_H
