#pragma once
#include <QObject>
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/Record.h"
#include "SRC/BusinessLogic/User.h"
#include <fstream>
#include <iostream>
#include <list>
#include <cstdio>


class User_File_Operations : public QObject
{
    Q_OBJECT
public:
    explicit User_File_Operations(std::shared_ptr<Data> &d,QObject* pobj=nullptr);
    void clearData();
    void loadData(const std::string& login, const std::string& password);
    bool isUserCreated(const std::string& login, const std::string& password);
    std::list<std::string> getUsersNames()const;
    void deleteUser(const std::string& login,const std::string& password);
    bool changedPassword(const std::string& login,const std::string& oldPassword,const std::string& newPassword);

private slots:
    void saveData()const;

signals:
    void dataIsLoaded();
    void wrongPassword();

private:
    std::shared_ptr<Data> pData;
    std::string dataFileName;
    std::string settingsFileName="settings.ac";
    std::vector<User> users;

    bool userIsOnList(const User& user)const;
    bool checkPassword(const User& userChecking);
    void loadUsers();
    void saveUsers();
};


