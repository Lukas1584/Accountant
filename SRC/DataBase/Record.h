#pragma once
#include <string>
#include <sstream>
#include <iostream>

constexpr int coloumnsCount=6;
constexpr char separatorRecord='~';

class Record{

public:

    enum class Type{
        PROFIT=1, LOSS
    };
    enum class Currency{
        USD=1, BYR, RUB, EUR
    };

    int columns() const;
    void clear();
    bool isNotEmpty() const;
    bool operator<(const Record& rhs) const;

    std::string getDate()const;
    Type getType()const;
    std::string getCategory()const;
    std::string getDescription()const;
    float getSum()const;
    Record::Currency getCurrency()const;

    void setDate(const std::string& d);
    void setType(const Record::Type t);
    void setCategory(const std::string& c);
    void setDescription(const std::string& d);
    void setSum(const float s);
    void setCurrency(const Record::Currency c);

    friend std::istream& operator>>(std::istream& dataStream, Record& rhs);
    friend std::ostream& operator<<(std::ostream& dataStream, const Record& rhs);

private:
    std::string date;
    Type type;
    std::string category;
    std::string description;
    float sum;
    Currency currency;
};

