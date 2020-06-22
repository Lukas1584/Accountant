#include "User_File_Operations.h"

User_File_Operations::User_File_Operations(Data* d) : QObject(),pData(d)
{
    settingsFileName="settings.ac";
    loadUsers();
}

bool User_File_Operations::isUserCreated(const QString& login, const QString& password){
    User user(login,password);
    if(userIsOnList(user)){
        return false;
    }
    users.push_back(user);
    saveUsers();
    dataFileName=user.login+".dat";
    saveData();
    emit dataIsLoaded();
    return true;
}

void User_File_Operations::saveUsers(){
    std::sort(users.begin(),users.end());
    QFile settings(settingsFileName);
    if(settings.open(QIODevice::WriteOnly)){
        QDataStream stream(&settings);
        stream.setVersion(QDataStream::Qt_5_15);
        for(auto i:users)
        stream<<i;
        settings.close();
    }
}

bool User_File_Operations::userIsOnList(const User& user) const{
    for(auto i:users){
        if(user.login==i.login){
            return true;
        }
    }
    return false;
}

void User_File_Operations::loadUsers(){
    QFile settings(settingsFileName);
    if(settings.open(QIODevice::ReadOnly)){
        QDataStream stream(&settings);
        stream.setVersion(QDataStream::Qt_5_15);
        while(!settings.atEnd()){
            User userReaded;
            stream>>userReaded;
            users.push_back(userReaded);
        }
    }
    settings.close();
}

QStringList User_File_Operations::getUsersNames() const{
    QStringList usersList;
    for(auto i:users)
        usersList.push_back(i.login);
    return usersList;
}

bool User_File_Operations::checkPassword(const User& userChecking){
    for(auto i:users){
        if(userChecking==i)
            return true;
    }
    emit wrongPassword();
    return false;
}

void User_File_Operations::loadData(const QString& login, const QString& password){
    User user(login,password);
    if(checkPassword(user)){
        dataFileName=user.login+".dat";
        QFile data(dataFileName);
        if(data.open(QIODevice::ReadOnly)){
            QDataStream stream(&data);
            stream.setVersion(QDataStream::Qt_5_15);
            stream>>(*pData);
            data.close();
        }
        emit dataIsLoaded();
    }
}

void User_File_Operations::saveData() const{
    QFile data(dataFileName);
    if(data.open(QIODevice::WriteOnly)){
        QDataStream stream(&data);
        stream.setVersion(QDataStream::Qt_5_15);
        stream<<pData;
    }
   data.close();
}

void User_File_Operations::clearData(){
    pData->clear();
}

void User_File_Operations::deleteUser(const QString& login,const QString& password){
    User userDeleting(login,password);
    dataFileName=userDeleting.login+".dat";
    if (checkPassword(userDeleting)){
        for(int i=0;i<users.size();i++){
            if(userDeleting==users[i]){
                users.erase(users.begin()+i);
                saveUsers();
                QFile(dataFileName).remove();
            }
        }
    }
}

bool User_File_Operations::changedPassword(const QString &login, const QString &oldPassword, const QString &newPassword){
    User userOldPassword(login,oldPassword);
    User userNewPassword(login,newPassword);
    for(int i=0; i<users.size();i++){
        if(users[i]==userOldPassword){
            users[i]=userNewPassword;
            saveUsers();
            return true;
        }
    }
    emit wrongPassword();
    return false;
}
