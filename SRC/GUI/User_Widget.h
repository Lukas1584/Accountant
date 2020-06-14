#pragma once
#include <QWidget>
#include <QtWidgets>
#include "SRC/BusinessLogic/User_File_Operations.h"

class User_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit User_Widget(User_File_Operations* ufo);

signals:
    void addUser(QString login,QString password);
private slots:
    void btnNewUserClicked();

private:
    User_File_Operations* pUserFileOperations;
    QPushButton* pBtnNewUser;
    QPushButton* pBtnLogIn;
    QPushButton* pBtnExit;

    QLineEdit* pLedPassword;
    QComboBox* pCbxUserName;

};


