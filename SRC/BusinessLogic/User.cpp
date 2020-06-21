#include "User.h"

User::User(){};

User::User(const QString& log,const QString& pass):login(log),password(pass){
}

bool User::operator==(const User& rhs) const{
    return (login==rhs.login)&&(password==rhs.password);
}

bool User::operator!=(const User& rhs) const{
    return !(login==rhs.login)&&(password==rhs.password);
}

QDataStream& operator>>(QDataStream& stream,User& user){
    stream>>user.login;
    stream>>user.password;
    return stream;
}

QDataStream& operator<<(QDataStream& stream,const User& user){
    stream<<user.login;
    stream<<user.password;
    return stream;
}

bool User::operator<(const User& rhs)const{
    return login<rhs.login;
}
