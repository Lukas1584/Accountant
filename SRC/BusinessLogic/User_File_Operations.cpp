#include "User_File_Operations.h"

User_File_Operations::User_File_Operations(std::shared_ptr<AbstractData>& d,std::shared_ptr<AbstractDataFileOperations> operations):
    pData(d),pOperations(operations){
    loadUsers();
}

bool User_File_Operations::isUserCreated(const std::string& login, const std::string& password){
    User user(login,password);
    if(userIsOnList(user)){
        return false;
    }
    users.push_back(user);
    saveUsers();
    dataFileName=user.getLogin()+".dat";
    saveData();
    return true;
}

void User_File_Operations::saveUsers(){
    std::sort(users.begin(),users.end());
    std::ofstream settings{settingsFileName,std::ios_base::binary};
    for(const User& i:users)
    settings<<i;
}

bool User_File_Operations::userIsOnList(const User& user) const{
    for(const auto& i:users)
        if(user.getLogin()==i.getLogin())
            return true;
    return false;
}

void User_File_Operations::loadUsers(){
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

std::list<std::string> User_File_Operations::getUsersNames() const{
    std::list<std::string> usersList;
    for(const auto& i:users)
        usersList.push_back(i.getLogin());
    return usersList;
}

bool User_File_Operations::checkPassword(const User& userChecking){
    for(const auto& i:users){
        if(userChecking==i)
            return true;
    }
    return false;
}

void User_File_Operations::clearData(){
    pData->clear();
}

bool User_File_Operations::deleteUser(const std::string& login,const std::string& password){
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

bool User_File_Operations::changedPassword(const std::string &login, const std::string &oldPassword, const std::string &newPassword){
    User userOldPassword(login,oldPassword);
    User userNewPassword(login,newPassword);
    for(unsigned int i=0; i<users.size();i++){
        if(users[i]==userOldPassword){
            users[i]=userNewPassword;
            saveUsers();
            return true;
        }
    }
    return false;
}

bool User_File_Operations::loadData(const std::string& login, const std::string& password){
    User user(login,password);
    if(checkPassword(user)){
        dataFileName=user.getLogin()+".dat";
        pOperations->loadFromFile(dataFileName);
        return true;
    }
    return false;
}

void User_File_Operations::saveData() const{
    pOperations->saveToFile(dataFileName);
}
