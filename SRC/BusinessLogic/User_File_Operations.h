#pragma once
#include <QObject>
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/Record.h"
#include <QFile>


class User_File_Operations : public QObject
{
    Q_OBJECT
public:
    explicit User_File_Operations(Data* d);
    QStringList getUsersNames();

public slots:
    void userCreation(QString login, QString password);
    void loadData(QString login, QString password);

signals:


private:
    Data* pData;
};


