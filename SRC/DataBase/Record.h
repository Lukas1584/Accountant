#pragma once
#include <string>
#include <QDate>

class Record
{

public:
    // int id;
    QDate date;
    enum Type{
        PROFIT, LOSS
    };
    std::string category;
    std::string description;
    float sum;
    enum Currency
    {
        USD, BYR, RUB, EUR
    };

};


