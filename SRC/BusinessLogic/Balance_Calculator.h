#pragma once
#include <QObject>
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/Record.h"
#include <QDebug>

constexpr int year=0;
constexpr int month=1;

class Balance_Calculator:public QObject
{
    Q_OBJECT
public:
    explicit Balance_Calculator(std::shared_ptr<Data>& data, QObject* parent=0);
    std::string getBalance()const;
    void setCurrentDate(const std::string& date);

private:
    std::shared_ptr<Data> pData;
    std::string currentDate;

    std::string balance(const int period, const Record::Currency currency)const;
    std::string minusYear()const;
    std::string minusMonth()const;
    std::string balanceCalculate(const std::string& dateFrom,const Record::Currency currency)const;
};


