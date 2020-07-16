#include "Record.h"

std::istream& operator>>(std::istream& dataStream, Record& rhs){
    rhs.clear();
    char c;
    while(dataStream.get(c) && c!=separatorRecord){
        rhs.date += c;
    }

    int typeInt=0;
    dataStream>>typeInt;
    if(typeInt==static_cast<int>(Record::Type::PROFIT))
        rhs.type=Record::Type::PROFIT;
    if(typeInt==static_cast<int>(Record::Type::LOSS))
        rhs.type=Record::Type::LOSS;

    dataStream.get(c); //separatorRecord
    while(dataStream.get(c) && c!=separatorRecord){
        rhs.category += c;
    }
    while(dataStream.get(c) && c!=separatorRecord){
        rhs.description += c;
    }

    dataStream>>rhs.sum;
    dataStream.get(c); //separatorRecord

    int currencyInt=0;
    dataStream>>currencyInt;
    switch(currencyInt){
    case(static_cast<int>(Record::Currency::BYR)):
        rhs.currency=Record::Currency::BYR;
        break;
    case(static_cast<int>(Record::Currency::USD)):
        rhs.currency=Record::Currency::USD;
        break;
    case(static_cast<int>(Record::Currency::EUR)):
        rhs.currency=Record::Currency::EUR;
        break;
    case(static_cast<int>(Record::Currency::RUB)):
        rhs.currency=Record::Currency::RUB;
        break;
    }
    dataStream.get(c); // '\n'
    return dataStream;
}

std::ostream& operator<<(std::ostream& dataStream,const Record& rhs){
    dataStream<<rhs.date<<separatorRecord;
    dataStream<<static_cast<int>(rhs.type)<<separatorRecord;
    dataStream<<rhs.category<<separatorRecord;
    dataStream<<rhs.description<<separatorRecord;
    dataStream<<rhs.sum<<separatorRecord;
    dataStream<<static_cast<int>(rhs.currency)<<'\n';
    return dataStream;
}

int Record::columns()const{
    return coloumnsCount;
}

void Record::clear(){
    date="";
    category="";
    description="";
    sum=0;
}

bool Record::isNotEmpty() const{
    return (sum)?true:false;
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

float Record::getSum()const{
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

void Record::setSum(const float s){
    sum=s;
}

void Record::setCurrency(const Record::Currency c){
    currency=c;
}
