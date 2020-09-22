#pragma once
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/DataOperations.h"
#include "SRC/BusinessLogic/User.h"
#include <fstream>
#include <iostream>
#include <list>
#include <cstdio>


class User_File_Operations{

public:
    explicit User_File_Operations(std::shared_ptr<AbstractData> &d,std::shared_ptr<AbstractDataFileOperations> operations);

    void clearData();
    bool loadData(const std::string& login, const std::string& password);
    void saveData()const;

    bool isUserCreated(const std::string& login, const std::string& password);
    std::list<std::string> getUsersNames()const;
    bool deleteUser(const std::string& login,const std::string& password);
    bool changedPassword(const std::string& login,const std::string& oldPassword,const std::string& newPassword);

private:
    std::shared_ptr<AbstractData> pData;
    std::shared_ptr<AbstractDataFileOperations> pOperations;
    std::string dataFileName;
    std::string settingsFileName="settings.ac";
    std::vector<User> users;

    bool userIsOnList(const User& user)const;
    bool checkPassword(const User& userChecking);
    void loadUsers();
    void saveUsers();
};
