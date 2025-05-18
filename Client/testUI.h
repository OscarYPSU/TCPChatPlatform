#ifndef TESTUI_H
#define TESTUI_H

#include "ui_testUI.h"  // <- auto-generated from testUI.ui
#include "main.h"
#include<winsock2.h>

class TestUI: public QMainWindow {
    Q_OBJECT
    public:
        explicit TestUI(SOCKET sock, QWidget *parent = nullptr);

    private slots:
        void onSendButtonClicked(); // 👈 Slot (function) to handle the click


    private:
        Ui::TestUI ui;
        main client;
        SOCKET clientsock;
};

#endif // TESTUI_H
