#pragma once
#include <QtWidgets>
#include "SRC/BusinessLogic/User_File_Operations.h"
#include "SRC/GUI/Password_Widget.h"
#include "SRC/GUI/Change_Password_Widget.h"

class User_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit User_Widget(User_File_Operations* user,QWidget* parent=nullptr);

signals:
    void disableMainWindow();
    void enableMainWindow();
    void exitUser();

private slots:
    void wrongPassword();
    void setWorkView();
    void btnNewUserClicked();
    void logIn();
    void changeUser();
    void addUser(const QString& login,const QString& password);
    void deleteUser();
    void changePassword();
    void changingPassword(const QString& oldPassword,const QString& newPassword);
    void cancelNewUser();
    void cancelChangePassword();

private:
    std::shared_ptr<Password_Widget> wdgPassword;
    std::shared_ptr<Change_Password_Widget> wdgChangePassword;

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

    void setStartView();
    void nameAlreadyExists();
    QStringList convertToStringist(const std::list<std::string>& listStd)const;
};


