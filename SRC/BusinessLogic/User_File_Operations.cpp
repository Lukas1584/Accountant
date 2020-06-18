#include "User_File_Operations.h"

User_File_Operations::User_File_Operations(Data* d) : QObject(),pData(d)
{
    settingsFileName="settings.ac";
    loadUsersList();
}

bool User_File_Operations::isUserCreated(const QString& login, const QString& password){
    User user(login,password);
    if(userIsOnList(user)){
        return false;
    }
    QFile settings(settingsFileName);
    if(settings.open(QIODevice::WriteOnly|QIODevice::Append)){
        QDataStream stream(&settings);
        stream.setVersion(QDataStream::Qt_5_15);
        stream<<user;
        settings.close();

        dataFileName=user.login+".dat";
        QFile newUser(dataFileName);
        newUser.open(QIODevice::WriteOnly);
        newUser.close();
        loadUsersList();
        emit dataIsLoaded();
        return true;
    }
    return false;
}

bool User_File_Operations::userIsOnList(const User& user){
    for(auto i:usersList){
        if(user.login==i){
            return true;
        }
    }
    return false;
}

void User_File_Operations::loadUsersList(){
    usersList.clear();
    QFile settings(settingsFileName);
    if(settings.open(QIODevice::ReadOnly)){
        QDataStream stream(&settings);
        stream.setVersion(QDataStream::Qt_5_15);
        while(!settings.atEnd()){
            User userReaded;
            stream>>userReaded;
            if(stream.status()!= QDataStream::Ok)
            {
                qDebug("Ошибка чтения файла");
            }
            usersList.push_back(userReaded.login);
        }
    }
    settings.close();
}

QStringList User_File_Operations::getUsersNames(){
    return usersList;
}

bool User_File_Operations::checkPassword(const User& userChecking){
    QFile settings(settingsFileName);
    if(settings.open(QIODevice::ReadOnly)){
        QDataStream stream(&settings);
        stream.setVersion(QDataStream::Qt_5_15);
        while(!settings.atEnd()){
            User userReaded;
            stream>>userReaded;
            if(stream.status()!= QDataStream::Ok)
            {
                qDebug("Ошибка чтения файла");
            }
            if(userChecking==userReaded){
                settings.close();
                return true;
            }
        }
        settings.close();
    }
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
            stream>>pData;
            if(stream.status()!= QDataStream::Ok)
            {
                qDebug("Ошибка чтения файла");
            }
            data.close();
            //addDataTemp(); ///////////////////////////////////////////////////////
        }
        emit dataIsLoaded();
    }
    else emit wrongPassword();
}

void User_File_Operations::saveData(){
    QFile data(dataFileName);
    if(data.open(QIODevice::WriteOnly)){
        QDataStream stream(&data);
        stream.setVersion(QDataStream::Qt_5_15);
        stream<<pData;
        if(stream.status() != QDataStream::Ok)
        {
            qDebug("Ошибка записи");
        }
    }
   data.close();
}

void User_File_Operations::clearData(){
    pData->clear();
}

//void User_File_Operations::addDataTemp(){
//    for(int i=0;i<10;i++){
//        Record rec;
//        rec.date=QDate(QDate::currentDate());
//        rec.category="Тестовая категория";
//        rec.description="Тестовая запись";
//        rec.sum=10*(i+1);
//        rec.type=Record::PROFIT;
//        rec.currency=Record::BYR;
//        pData->add(rec);
//    }
//}
