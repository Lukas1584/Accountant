#pragma once
#include <QWidget>
#include <QtWidgets>
#include "SRC/BusinessLogic/User_File_Operations.h"
#include "Password_Widget.h"

class User_Widget : public QWidget
{
    Q_OBJECT
public:
    User_Widget(User_File_Operations* ufo);

signals:
    void disableMainWindow();
    void enableMainWindow();

public slots:
    void wrongPassword();
    void setWorkView();

private slots:
    void btnNewUserClicked();
    void logIn();
    void changeUser();
    void addUser(QString,QString);

private:
    Password_Widget* wdgPassword;
    User_File_Operations* pUserFileOperations;

    QPushButton* pBtnNewUser;
    QPushButton* pBtnLogIn;
    QPushButton* pBtnDeleteUser;
    QPushButton* pBtnChangeUser;
    QPushButton* pBtnChangePassword;

    QLineEdit* pLedPassword;
    QComboBox* pCbxUserName;

    QLabel* pLblUserName;
    QLabel* pLblPassword;
    QGridLayout* pGrdMain;

    void setStartView();

    void nameAlreadyExists();
};


