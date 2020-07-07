#include "Record.h"

std::istream& operator>>(std::istream& dataStream, Record& rhs){
    rhs.clear();
    char c;
    while(dataStream.get(c) && c!=separatorRecord){
        rhs.date += c;
    }

    int typeInt=0;
    dataStream>>typeInt;
    if(typeInt==Record::Type::PROFIT)
        rhs.type=Record::PROFIT;
    if(typeInt==Record::LOSS)
        rhs.type=Record::LOSS;

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
    case(Record::BYR):
        rhs.currency=Record::BYR;
        break;
    case(Record::USD):
        rhs.currency=Record::USD;
        break;
    case(Record::EUR):
        rhs.currency=Record::EUR;
        break;
    case(Record::RUB):
        rhs.currency=Record::RUB;
        break;
    }
    dataStream.get(c); // '\n'
    return dataStream;
}

std::ostream& operator<<(std::ostream& dataStream,const Record& rhs){
    dataStream<<rhs.date<<separatorRecord;
    dataStream<<rhs.type<<separatorRecord;
    dataStream<<rhs.category<<separatorRecord;
    dataStream<<rhs.description<<separatorRecord;
    dataStream<<rhs.sum<<separatorRecord;
    dataStream<<rhs.currency<<'\n';
    return dataStream;
}

std::string Record::convert(const int column)const{
    switch (column){
    case 0:
        return date;
    case 1:
        switch (type) {
        case Record::PROFIT:
            return "Прибыль";
        case Record::LOSS:
            return "Убыток";
        default:
            return "";
        }
    case 2:
        return category;
    case 3:
        return description;
    case 4:{
        std::stringstream ss;
        ss<<sum;
        std::string str;
        ss>>str;
        return str;
    }
    case 5:
        switch (currency) {
        case Record::USD:
            return "USD";
        case Record::BYR:
            return "BYR";
        case Record::RUB:
            return "RUB";
        case Record::EUR:
            return "EUR";
        default:
            return "";
        }
    default:
        return "";
    }
}

int Record::columns()const{
    return coloumnsCount;
}

void Record::setData(const int column,const std::string& value){
    switch (column){
    case 0:
        date=value;
        return;
    case 1:
        if(value=="Прибыль"){
            type=Record::PROFIT;
            return;
        }
        if(value=="Убыток"){
            type=Record::LOSS;
            return;
        }
    case 2:
        category=value;
        return;
    case 3:
        description=value;
        return;
    case 4:{
        std::stringstream ss;
        ss<<value;
        ss>>sum;
        return;
    }
    case 5:
        if(value=="USD"){
            currency=Record::USD;
            return;
        }
        if(value=="BYR"){
            currency=Record::BYR;
            return;
        }
        if(value=="RUB"){
            currency=Record::RUB;
            return;
        }
        if(value=="EUR"){
            currency=Record::EUR;
            return;
        }
    default:
        return;
    }
}

std::string Record::getCategory() const{
    return category;
}
std::string Record::getDescription()const{
    return description;
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

