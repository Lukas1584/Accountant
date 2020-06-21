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
    User_File_Operations(Data* d);
    void clearData();
    void loadData(const QString& login, const QString& password);
    bool isUserCreated(const QString& login, const QString& password);
    QStringList getUsersNames()const;
    void deleteUser(const QString& login,const QString& password);
    bool changedPassword(const QString& login,const QString& oldPassword,const QString& newPassword);

public slots:
    void saveData()const;

signals:
    void dataIsLoaded();
    void wrongPassword();

private:
    Data* pData;
    QString dataFileName;
    QString settingsFileName;
    QVector<User> users;

    bool userIsOnList(const User& user)const;
    bool checkPassword(const User& userChecking);
    void loadUsers();
    void saveUsers();
};


