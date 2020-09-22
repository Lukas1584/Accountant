#pragma once
#include <string>
#include <iostream>

class User{
public:
    User(){}
    User(const std::string& log,const std::string& pass);
    bool operator==(const User& rhs) const;
    bool operator!=(const User& rhs) const;
    bool operator<(const User& rhs)const;
    bool isNotEmpty() const;
    std::string getLogin() const;

    friend std::istream& operator>>(std::istream& stream,User& user);
    friend std::ostream& operator<<(std::ostream& stream,const User& user);
private:
    std::string login;
    std::string password;
    void clear();
};


