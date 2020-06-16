#include "User_File_Operations.h"

User_File_Operations::User_File_Operations(Data* d) : QObject(),pData(d)
{
//    for(int i=0;i<10;i++){
//        Record rec;
//        rec.id=i;
//        rec.date=QDate(QDate::currentDate());
//        rec.category="Тестовая категория";
//        rec.description="Тестовая запись";
//        rec.sum=10*(i+1);
//        rec.type=Record::PROFIT;
//        rec.currency=Record::BYR;
//        pData->add(rec);
//    }
}

bool User_File_Operations::userIsOnList(const User& user){
    QFile settings("settings.ac");
    if(settings.open(QIODevice::ReadOnly)){
        QDataStream stream(&settings);
        stream.setVersion(QDataStream::Qt_5_15);
        while(!settings.atEnd()){
            User readedUser;
            stream>>readedUser;
            if(stream.status()!= QDataStream::Ok)
            {
                qDebug("Ошибка чтения файла");
            }
            if(user.login==readedUser.login){
                settings.close();
                return true;
            }
        }
    }
    settings.close();
    return false;
}

void User_File_Operations::userCreation(const QString& login, const QString& password){
    User user(login,password);
    if(userIsOnList(user)){
        emit nameAlreadyExists();
        return;
    }
    QFile settings("settings.ac");
    if(settings.open(QIODevice::WriteOnly|QIODevice::Append)){
        QDataStream stream(&settings);
        stream.setVersion(QDataStream::Qt_5_15);
        stream<<user;
        if(stream.status()!= QDataStream::Ok)
        {
            qDebug("Ошибка чтения файла");
        }
        settings.close();

        dataFileName=user.login+".dat";
        QFile newUser(dataFileName);
        newUser.open(QIODevice::WriteOnly);
        newUser.close();
    }
}

QStringList User_File_Operations::getUsersNames(){
    QFile settings("settings.ac");
    QStringList names;
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
            names.push_back(userReaded.login);
        }
    }
    settings.close();
    return names;
}

void User_File_Operations::checkPassword(const QString& login, const QString& password){
    User userChecking(login,password);
    QFile settings("settings.ac");
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
                loadData(userChecking.login);
                settings.close();
                return;
            }
        }
        settings.close();
        emit wrongPassword();
        return;
    }
}

void User_File_Operations::loadData(const QString& login){
    dataFileName=login+".dat";
    QFile data(dataFileName);
    if(data.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&data);
        stream.setVersion(QDataStream::Qt_5_15);
        stream>>pData;
        if(stream.status()!= QDataStream::Ok)
        {
            qDebug("Ошибка чтения файла");
        }
    data.close();
    }
    emit dataIsLoaded();
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

