#include "User.h"

User::User(){};

User::User(const std::string &log, const std::string &pass):login(log),password(pass){
}

bool User::operator==(const User& rhs) const{
    return (login==rhs.login)&&(password==rhs.password);
}

bool User::operator!=(const User& rhs) const{
    return !(*this==rhs);
}

bool User::operator<(const User& rhs)const{
    return login<rhs.login;
}

void User::clear(){
    login="";
    password="";
}

bool User::isNotEmpty() const{
    return (login!="")?true:false;
}

std::string User::getLogin() const{
    return login;
}

std::istream& operator>>(std::istream& stream,User& user){
    user.clear();
    char c;
    while(stream.get(c) && c!=separator){
        user.login += c;
    }
    while(stream.get(c) && c!=separator){
        user.password += c;
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream,const User& user){
    stream<<user.login<<separator<<user.password<<separator;
    return stream;
}


