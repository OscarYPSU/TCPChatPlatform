//
// Created by oskhy on 5/20/2025.
//

#ifndef NEWPAGE_H
#define NEWPAGE_H

#include <QMainWindow>
#include "ui_frontPage.h"
#include "../sqlite3/sqlite3.h"
#include "../sqlite3/SQL.h"

class frontPage: public QMainWindow {
    Q_OBJECT

    public:
        explicit frontPage(sqlite3 *db, QWidget *parent = nullptr);


    private slots:
        void registerButtonClicked();
        void loginButtonClicked();

    private:
        Ui::frontPage newUI;
        sqlite3 *db;
        SQL sql;
};

#endif //NEWPAGE_H
