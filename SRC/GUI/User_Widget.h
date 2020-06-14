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

public slots:
    void nameAlreadyExists();
    void slotAddUser(QString,QString);

private slots:
    void btnNewUserClicked();
    void slotLogIn();


private:
    Password_Widget* wdgPassword;
    User_File_Operations* pUserFileOperations;
    QPushButton* pBtnNewUser;
    QPushButton* pBtnLogIn;
    QPushButton* pBtnExit;

    QLineEdit* pLedPassword;
    QComboBox* pCbxUserName;

    QLabel* pLblUserName;
    QLabel* pLblPassword;
    QGridLayout* pGrdMain;


    void setStartView();
    void setWorkView();

};


