#include "UserFileOperations.h"

UserFileOperations::UserFileOperations(std::shared_ptr<AbstractData>& d,std::shared_ptr<AbstractDataFileOperations> operations):
    pData(d),pOperations(operations){
    loadUsers();
}

bool UserFileOperations::isUserCreated(const std::string& login, const std::string& password){
    User user(login,password);
    if(userIsOnList(user)){
        return false;
    }
    users.push_back(user);
    saveUsers();
    dataFileName=user.getLogin()+".dat";
    saveData();
    currentUser=user;
    return true;
}

void UserFileOperations::saveUsers(){
    std::sort(users.begin(),users.end());
    std::ofstream settings{settingsFileName,std::ios_base::binary};
    for(const User& i:users)
    settings<<i;
}

bool UserFileOperations::userIsOnList(const User& user) const{
    for(const auto& i:users)
        if(user.getLogin()==i.getLogin())
            return true;
    return false;
}

void UserFileOperations::loadUsers(){
    std::ifstream settings{settingsFileName,std::ios_base::binary};
    if(settings){
        while(!settings.eof()){
            User userReaded;
            settings>>userReaded;
            if(userReaded.isNotEmpty())
                users.push_back(userReaded);
        }
    }
}

std::list<std::string> UserFileOperations::getUsersNames() const{
    std::list<std::string> usersList;
    for(const auto& i:users)
        usersList.push_back(i.getLogin());
    return usersList;
}

bool UserFileOperations::checkPassword(const User& userChecking) const{
    for(const auto& i:users){
        if(userChecking==i)
            return true;
    }
    return false;
}

void UserFileOperations::clearData(){
    pData->clear();
    User user;
    currentUser=user;
}

bool UserFileOperations::deleteUser(const std::string& login,const std::string& password){
    User userDeleting(login,password);
    if (checkPassword(userDeleting)){
        for(unsigned int i=0;i<users.size();i++){
            if(userDeleting==users[i]){
                users.erase(users.begin()+i);
                saveUsers();
                dataFileName=userDeleting.getLogin()+".dat";
                std::remove(dataFileName.c_str());
                return true;
            }
        }
    }
    return false;
}

bool UserFileOperations::changedPassword(const std::string &login, const std::string &oldPassword, const std::string &newPassword){
    User userOldPassword(login,oldPassword);
    User userNewPassword(login,newPassword);
    for(unsigned int i=0; i<users.size();i++){
        if(users[i]==userOldPassword){
            users[i]=userNewPassword;
            saveUsers();
            currentUser=userNewPassword;
            return true;
        }
    }
    return false;
}

bool UserFileOperations::loadData(const std::string& login, const std::string& password){
    User user(login,password);
    if(checkPassword(user)){
        dataFileName=user.getLogin()+".dat";
        pOperations->loadFromFile(dataFileName);
        currentUser=user;
        return true;
    }
    return false;
}

void UserFileOperations::saveData()const{
    pOperations->saveToFile(dataFileName);
}

std::string UserFileOperations::getUserName()const{
    return currentUser.getLogin();
}
