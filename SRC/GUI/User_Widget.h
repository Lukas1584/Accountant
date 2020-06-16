#pragma once
#include <QWidget>
#include <QtWidgets>
#include "SRC/BusinessLogic/User_File_Operations.h"
#include "Password_Widget.h"

class User_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit User_Widget(User_File_Operations* ufo);

signals:
    void addUser(QString,QString);
    void logIn(QString,QString);
    void disableMainWindow();
    void enableMainWindow();
    void clearData();

public slots:
    void nameAlreadyExists();
    void slotAddUser(QString,QString);
    void wrongPassword();
    void enableMainWindowFromPassword();
    void setWorkView();

private slots:
    void btnNewUserClicked();
    void slotLogIn();
    void changeUser();

private:
    Password_Widget* wdgPassword;
    User_File_Operations* pUserFileOperations;

    QPushButton* pBtnNewUser;
    QPushButton* pBtnLogIn;
    QPushButton* pBtnDeleteUser;
    QPushButton* pBtnChangeUser;

    QLineEdit* pLedPassword;
    QComboBox* pCbxUserName;

    QLabel* pLblUserName;
    QLabel* pLblPassword;
    QGridLayout* pGrdMain;

    void setStartView();
};


