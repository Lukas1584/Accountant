#pragma once
#include <QtWidgets>
#include "SRC/BusinessLogic/BusinessLogic.h"
#include "SRC/GUI/PasswordWidget.h"
#include "SRC/GUI/ChangePasswordWidget.h"

class UserWidget : public QWidget{
    Q_OBJECT
public:
    UserWidget(std::shared_ptr<AbstractBusinessLogic> logic,QWidget* parent=nullptr);

signals:
    void disableMainWindow();
    void enableMainWindow();
    void exitUser();
    void dataIsLoaded();

private slots:
    void newUserClicked();
    void logIn();
    void changeUser();
    void addUser(const QString& login,const QString& password);
    void deleteUser();
    void changePassword();
    void changingPassword(const QString& oldPassword,const QString& newPassword);
    void cancelNewUser();
    void cancelChangePassword();
    void clearPassword();

private:
    std::unique_ptr<PasswordWidget> wdgPassword;
    std::unique_ptr<ChangePasswordWidget> wdgChangePassword;
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

    void wrongPassword();
    void setStartView();
    void nameAlreadyExists();
    void setWorkView();
    QStringList convertToQstringList(const std::list<std::string>& listStd)const;
};


