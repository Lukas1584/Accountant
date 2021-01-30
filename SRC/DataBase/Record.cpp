#include "Record.h"

unsigned int Record::columns()const{
    const unsigned int coloumnsCount=6;
    return coloumnsCount;
}

bool Record::operator<(const Record& rhs)const{
    if(date<rhs.date)
        return true;
    if(date>rhs.date)
        return false;
    if(category<rhs.category)
        return true;
    if(category>rhs.category)
        return false;
    if (description<rhs.description)
        return true;
    if (description>rhs.description)
        return false;
    if (sum<rhs.sum)
        return true;
    else
        return false;
}

double Record::getSum()const{
    return sum;
}

std::string Record::getDate()const{
    return date;
}

Record::Type Record::getType()const{
    return type;
}

std::string Record::getCategory()const{
    return category;
}

std::string Record::getDescription()const{
    return description;
}

Record::Currency Record::getCurrency()const{
    return currency;
}

void Record::setDate(const std::string& d){
    date=d;
}

void Record::setType(const Record::Type t){
    type=t;
}

void Record::setCategory(const std::string& c){
    category=c;
}

void Record::setDescription(const std::string& d){
    description=d;
}

void Record::setSum(const double s){
    sum=s;
}

void Record::setCurrency(const Record::Currency c){
    currency=c;
}

Record::Record(const RecordString &record){
    date=record.getDate();
    std::string typeString=record.getType();
    if(typeString=="Прибыль")
        type=Record::Type::PROFIT;
    if(typeString=="Убыток")
        type=Record::Type::LOSS;
    category=record.getCategory();
    description=record.getDescription();
    sum=record.getSum();
    std::string currencyString=record.getCurrency();
    if(currencyString=="USD")
        currency=Record::Currency::USD;
    if(currencyString=="BYR")
        currency=Record::Currency::BYR;
    if(currencyString=="RUB")
        currency=Record::Currency::RUB;
    if(currencyString=="EUR")
        currency=Record::Currency::EUR;
}

RecordString Record::convertToString()const{
    std::string typeString;
    if(type==Record::Type::LOSS)
        typeString="Убыток";
    if(type==Record::Type::PROFIT)
        typeString="Прибыль";
    std::string currencyString;
    if(currency==Record::Currency::BYR)
        currencyString="BYR";
    if(currency==Record::Currency::USD)
        currencyString="USD";
    if(currency==Record::Currency::RUB)
        currencyString="RUB";
    if(currency==Record::Currency::EUR)
        currencyString="EUR";
    return {date,typeString,category,description,sum,currencyString};
}

std::list<std::string> Record::getAllCurrencies() const{
    return {"USD","BYR","RUB","EUR"};
}
std::list<std::string> Record::getAllTypes() const{
    return {"Прибыль","Убыток"};
}
