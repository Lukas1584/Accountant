#pragma once
#include <QObject>
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/Record.h"
#include "SRC/BusinessLogic/User.h"
#include <QFile>
#include <QDataStream>


class User_File_Operations : public QObject
{
    Q_OBJECT
public:
    explicit User_File_Operations(Data* d);
    QStringList getUsersNames();

public slots:
    void userCreation(const QString& login, const QString& password);
    void checkPassword(const QString& login, const QString& password);
    void saveData();

signals:
    void nameAlreadyExists();
    void wrongPassword();
    void dataIsLoaded();

private:
    Data* pData;
    QString dataFileName;
    bool userIsOnList(const User& user);
    void loadData(const QString& login);
};


