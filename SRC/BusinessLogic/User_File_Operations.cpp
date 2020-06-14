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

void User_File_Operations::userCreation(QString login, QString password){
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

void User_File_Operations::loadData(QString login, QString password){




}




