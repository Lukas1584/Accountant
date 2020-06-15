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
    void userCreation(const QString& login, const QString& password);
    void checkPassword(const QString& login, const QString& password);

signals:
    void nameAlreadyExists();
    void wrongPassword();
    void dataIsLoaded();

private:
    Data* pData;

    bool userIsOnList(const QString& login);
    void loadData(const QString& login);
};


