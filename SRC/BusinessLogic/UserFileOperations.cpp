#include "UserFileOperations.h"

UserFileOperations::UserFileOperations(){
    loadUsers();
}

bool UserFileOperations::isUserCreated(const std::string& login, const std::string& password){
    User user(login,password);
    if(userIsOnList(user)){
        return false;
    }
    users.push_back(user);
    saveUsers();
    currentUser=user;
    return true;
}

void UserFileOperations::saveUsers(){
    std::sort(users.begin(),users.end());
    std::ofstream settings{settingsFileName};
    if(!settings) throw "File wasn't created";
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
    users.clear();
    std::ifstream settings{settingsFileName};
    if(settings){
        while(!settings.eof()){
            User userRead;
            settings>>userRead;
            if(userRead.isNotEmpty())
                users.push_back(userRead);
        }
    }
    //else throw "File doesn't exist";
}

std::list<std::string> UserFileOperations::getUsersNames() const{
    std::list<std::string> usersList;
    for(const auto& i:users)
        usersList.push_back(i.getLogin());
    return usersList;
}

bool UserFileOperations::checkPassword(const User& userChecking){
    for(const auto& i:users){
        if(userChecking==i){
            currentUser=userChecking;
            return true;
        }
    }
    return false;
}

bool UserFileOperations::deleteUser(const std::string& login,const std::string& password){
    User userDeleting(login,password);
    if (checkPassword(userDeleting)){
        unsigned int countUsers=users.size();
        for(unsigned int i=0;i<countUsers;i++){
            if(userDeleting==users[i]){
                users.erase(users.begin()+i);
                saveUsers();
                return true;
            }
        }
    }
    return false;
}

bool UserFileOperations::changedPassword(const std::string &login, const std::string &oldPassword, const std::string &newPassword){
    User userOldPassword(login,oldPassword);
    User userNewPassword(login,newPassword);
    unsigned int countUsers=users.size();
    for(unsigned int i=0; i<countUsers;i++){
        if(users[i]==userOldPassword){
            users[i]=userNewPassword;
            saveUsers();
            currentUser=userNewPassword;
            return true;
        }
    }
    return false;
}

std::string UserFileOperations::getUserName()const{
    return currentUser.getLogin();
}
