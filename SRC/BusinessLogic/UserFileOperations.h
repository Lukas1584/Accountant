#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include <string>
#include "SRC/DataBase/DataOperations.h"
#include "SRC/BusinessLogic/User.h"

class UserFileOperations{

public:
    UserFileOperations();

    bool isUserCreated(const std::string& login, const std::string& password);
    std::list<std::string> getUsersNames()const;
    bool deleteUser(const std::string& login,const std::string& password);
    bool changedPassword(const std::string& login,const std::string& oldPassword,const std::string& newPassword);
    std::string getUserName()const;
    bool checkPassword(const User& userChecking);

private:
    std::string settingsFileName="settings.ac";
    std::vector<User> users;
    User currentUser;

    bool userIsOnList(const User& user)const;
    void loadUsers();
    void saveUsers();
};
