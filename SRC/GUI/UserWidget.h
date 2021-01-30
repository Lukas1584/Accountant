#pragma once
#include <QtWidgets>
#include <memory>
#include <QString>
#include <QStringList>
#include <list>
#include <string>
#include "SRC/BusinessLogic/BusinessLogic.h"
#include "SRC/GUI/PasswordWidget.h"
#include "SRC/GUI/ChangePasswordWidget.h"

class UserWidget : public QWidget{
    Q_OBJECT
public:
    UserWidget(std::shared_ptr<AbstractBusinessLogic> logic,QWidget* parent);

signals:
    void exitUser();
    void dataIsLoaded();

private slots:
    void newUserClicked();
    void logIn();
    void changeUser();
    void addUser(const QString& login,const QString& password);
    void deleteUser();
    void changePassword();
    void changingPassword(const QString& oldPassword, const QString& newPassword);
    void clearPassword();

private:
    std::shared_ptr<AbstractBusinessLogic> pLogic;

    QPushButton* pBtnNewUser;
    QPushButton* pBtnLogIn;
    QPushButton* pBtnDeleteUser;
    QPushButton* pBtnChangeUser;
    QPushButton* pBtnChangePassword;

    QLineEdit* pLedPassword;
    QComboBox* pCbxUserName;

    QLabel* pLblUserName;
    QLabel* pLblPassword;

    void drawWindow();
    void connectButtons();
    void setStartView();
    void setWorkView();
    QStringList convertToQstringList(const std::list<std::string>& listStd)const;
};


