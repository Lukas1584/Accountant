#include "User_File_Operations.h"
#include <QDataStream>

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

bool User_File_Operations::userIsOnList(const QString& login){
    QFile settings("settings.ac");
    settings.open(QIODevice::ReadOnly); //проверка на ошибки
    while(!settings.atEnd()){
        QString str=settings.readLine();
        if(login==str.remove(str.size()-1,str.size())){
            settings.close();
            return true;
        }
        settings.readLine();
    }
    settings.close();
    return false;
}

void User_File_Operations::userCreation(const QString& login, const QString& password){
    if(userIsOnList(login)){
        emit nameAlreadyExists();
        return;
    }
    QFile settings("settings.ac");
    settings.open(QIODevice::WriteOnly|QIODevice::Append); //проверка на ошибки
    QString toSave=login+'\n'+password+'\n';
    settings.write(toSave.toUtf8().constData());
    settings.close();
    dataFileName=login+".dat";
    QFile newUser(dataFileName);
    newUser.open(QIODevice::WriteOnly); //проверка на ошибки
    newUser.close(); //направить поток дальше на выполнение программы
}

QStringList User_File_Operations::getUsersNames(){
    QFile settings("settings.ac");
    settings.open(QIODevice::ReadOnly); //проверка на ошибки
    QStringList names;
    while(!settings.atEnd()){
        QString userName=settings.readLine();
        names.push_back(userName.remove(userName.size()-1,userName.size()));
        settings.readLine();
    }
    settings.close();
    return names;
}

void User_File_Operations::checkPassword(const QString& login, const QString& password){
    QFile settings("settings.ac");
    settings.open(QIODevice::ReadOnly); //проверка на ошибки
    while(!settings.atEnd()){
        QString userName=settings.readLine();
        if(login==userName.remove(userName.size()-1,userName.size())){
            QString passwordFromFIle=settings.readLine();
            if(password==passwordFromFIle.remove(passwordFromFIle.size()-1,passwordFromFIle.size())){
                loadData(login);
                settings.close();
                return;
            }
            settings.close();
            emit wrongPassword();
            return;
        }
    }
}

void User_File_Operations::loadData(const QString& login){
//    if(pData) delete pData;
//    pData=new Data;
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


