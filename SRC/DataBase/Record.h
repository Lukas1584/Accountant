#pragma once
#include <string>
#include <sstream>
#include <list>
#include "SRC/BusinessLogic/RecordString.h"

class Record{

public:
    Record():sum(0){};
    Record(const RecordString&);

    enum class Type{
        PROFIT=1, LOSS
    };
    enum class Currency{
        USD=1, BYR, RUB, EUR
    };

    int columns()const;

    std::string getDate()const;
    Type getType()const;
    std::string getCategory()const;
    std::string getDescription()const;
    double getSum()const;
    Record::Currency getCurrency()const;

    void setDate(const std::string& d);
    void setType(const Record::Type t);
    void setCategory(const std::string& c);
    void setDescription(const std::string& d);
    void setSum(const double s);
    void setCurrency(const Record::Currency c);

    bool operator<(const Record& rhs) const;
    RecordString convertToString()const;
    std::list<std::string> getAllCurrencies()const;
    std::list<std::string> getAllTypes()const;
private:
    std::string date;
    Type type;
    std::string category;
    std::string description;
    double sum;
    Currency currency;
};

