#pragma once
#include <QString>
#include <QDataStream>

class User
{
public:
    User();
    User(QString log,QString pass);
    bool operator==(const User& rhs) const;
    bool operator!=(const User& rhs) const;
    bool operator<(const User& rhs) const;
    QString login;
    QString password;
};

QDataStream& operator>>(QDataStream& stream,User& user);
QDataStream& operator<<(QDataStream& stream,const User& user);
