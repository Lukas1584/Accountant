#pragma once
#include <QtWidgets>
#include "SRC/BusinessLogic/User_File_Operations.h"
#include "SRC/GUI/Password_Widget.h"
#include "SRC/GUI/Change_Password_Widget.h"



class User_Widget : public QWidget
{
    Q_OBJECT
public:
    User_Widget(User_File_Operations* ufo);

signals:
    void disableMainWindow();
    void enableMainWindow();
    void exitUser();

public slots:
    void wrongPassword();
    void setWorkView();

private slots:
    void btnNewUserClicked();
    void logIn();
    void changeUser();
    void addUser(const QString& login,const QString& password);
    void deleteUser();
    void changePassword();
    void changingPassword(const QString& oldPassword,const QString& newPassword);

private:
    Password_Widget* wdgPassword;
    Change_Password_Widget* wdgChangePassword;
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


