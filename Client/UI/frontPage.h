//
// Created by oskhy on 5/20/2025.
//

#ifndef NEWPAGE_H
#define NEWPAGE_H

#include <QMainWindow>
#include "ui_frontPage.h"
#include "../sqlQueries/sql.h"
#include <libpq-fe.h>
#pragma once

class frontPage: public QMainWindow {
    Q_OBJECT

    public:
        explicit frontPage(PGconn *conn, QWidget *parent = nullptr);


    private slots:
        void registerButtonClicked();
        void loginButtonClicked();

    private:
        Ui::frontPage newUI;
        PGconn *conn;
};

#endif //NEWPAGE_H
