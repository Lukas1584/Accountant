#include "User_File_Operations.h"
#include <QTextStream>

User_File_Operations::User_File_Operations(Data* d) : QObject(),pData(d)
{
    for(int i=0;i<10;i++){
        Record rec;
        rec.id=i;
        rec.date=QDate(QDate::currentDate());
        rec.category="Тестовая категория";
        rec.description="Тестовая запись";
        rec.sum=10*(i+1);
        rec.type=Record::PROFIT;
        rec.currency=Record::BYR;
        pData->add(rec);
    }
}

bool User_File_Operations::userIsOnList(const QString& login){
    QFile settings("settings.ac");
    settings.open(QIODevice::ReadOnly);
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
    settings.open(QIODevice::WriteOnly|QIODevice::Append);
    QString toSave=login+'\n'+password+'\n';
    settings.write(toSave.toUtf8().constData());
    settings.close();
    QString newFileName=login+".dat";
    QFile newUser(newFileName);
    newUser.open(QIODevice::WriteOnly);
    newUser.close();
}

QStringList User_File_Operations::getUsersNames(){
    QFile settings("settings.ac");
    settings.open(QIODevice::ReadOnly);
    QStringList names;
    QString str;
    while(!settings.atEnd()){
        str=settings.readLine();
        settings.readLine();
        names.push_back(str);
    }
    settings.close();
    return names;
}



void User_File_Operations::loadData(const QString& login, const QString& password){




}




