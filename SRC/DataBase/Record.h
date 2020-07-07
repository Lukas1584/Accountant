#pragma once
#include <string>
#include <sstream>
#include <iostream>

constexpr int coloumnsCount=6;
constexpr char separatorRecord='~';

class Record{

public:
    std::string convert(const int column) const;
    int columns() const;
    void setData(const int column,const std::string& value);
    std::string getCategory() const;
    std::string getDescription() const;
    void clear();
    bool isNotEmpty() const;
    bool operator<(const Record& rhs) const;

    friend std::istream& operator>>(std::istream& dataStream, Record& rhs);
    friend std::ostream& operator<<(std::ostream& dataStream, const Record& rhs);

private:
    std::string date;
    enum Type{
        PROFIT=1, LOSS
    }type;
    std::string category;
    std::string description;
    float sum=0;
    enum Currency{
        USD=1, BYR, RUB, EUR
    }currency;
};

