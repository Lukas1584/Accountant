#pragma once
#include <string>
#include <sstream>
#include <iostream>

constexpr int coloumnsCount=6;
constexpr char separatorRecord='~';

class Record{

public:
    int columns() const;
    void setData(const int column,const std::string& value);
    void clear();
    bool isNotEmpty() const;
    bool operator<(const Record& rhs) const;
    std::string at(const int column) const;
    float getSum()const;

    friend std::istream& operator>>(std::istream& dataStream, Record& rhs);
    friend std::ostream& operator<<(std::ostream& dataStream, const Record& rhs);

private:
    std::string date;
    enum Type{
        PROFIT=1, LOSS
    }type;
    std::string category;
    std::string description;
    float sum;
    enum Currency{
        USD=1, BYR, RUB, EUR
    }currency;
};

