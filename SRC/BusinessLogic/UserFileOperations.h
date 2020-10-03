#pragma once
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/DataOperations.h"
#include "SRC/BusinessLogic/User.h"
#include <fstream>
#include <iostream>
#include <list>

class UserFileOperations{

public:
    explicit UserFileOperations(std::shared_ptr<AbstractData> &d,std::shared_ptr<AbstractDataFileOperations> operations);

    void clearData();
    bool loadData(const std::string& login, const std::string& password);
    void saveData()const;

    bool isUserCreated(const std::string& login, const std::string& password);
    std::list<std::string> getUsersNames()const;
    bool deleteUser(const std::string& login,const std::string& password);
    bool changedPassword(const std::string& login,const std::string& oldPassword,const std::string& newPassword);
    std::string getUserName()const;

private:
    std::shared_ptr<AbstractData> pData;
    std::shared_ptr<AbstractDataFileOperations> pOperations;
    std::string dataFileName;
    std::string settingsFileName="settings.ac";
    std::vector<User> users;
    User currentUser;

    bool userIsOnList(const User& user)const;
    bool checkPassword(const User& userChecking)const;
    void loadUsers();
    void saveUsers();
};
