#include "Record.h"

QDataStream& operator>>(QDataStream& dataStream, Record& rhs){
    dataStream>>rhs.date;
    dataStream>>rhs.type;
    dataStream>>rhs.category;
    dataStream>>rhs.description;
    dataStream>>rhs.sum;
    dataStream>>rhs.currency;
    return dataStream;
}

QDataStream& operator<<(QDataStream& dataStream,const Record& rhs){
    dataStream<<rhs.date;
    dataStream<<rhs.type;
    dataStream<<rhs.category;
    dataStream<<rhs.description;
    dataStream<<rhs.sum;
    dataStream<<rhs.currency;
    return dataStream;
}

QVariant Record::convert(int column)const{
    switch (column){
    case 0:
        return QVariant(date);
    case 1:
        switch (type) {
        case Record::PROFIT:
            return "Прибыль";
        case Record::LOSS:
            return "Убыток";
        default:
            return QVariant();
        }
    case 2:
        return QVariant(category);
    case 3:
        return QVariant(description);
    case 4:
        return QVariant(sum);
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
            return QVariant();
        }
    default:
        return QVariant();
    }
}

int Record::columns()const
{
    return 6;
}

void Record::setData(const int column,const QVariant& value){
    switch (column){
    case 0:
        date=value.toDate();
        return;
    case 1:
        if(value.toString()=="Прибыль"){
            type=Record::PROFIT;
            return;
        }
        if(value.toString()=="Убыток"){
            type=Record::LOSS;
            return;
        }
    case 2:
        category=value.toString();
        return;
    case 3:
        description=value.toString();
        return;
    case 4:
        sum=value.toFloat();
        return;
    case 5:
        if(value.toString()=="USD"){
            currency=Record::USD;
            return;
        }
        if(value.toString()=="BYR"){
            currency=Record::BYR;
            return;
        }
        if(value.toString()=="RUB"){
            currency=Record::RUB;
            return;
        }
        if(value.toString()=="EUR"){
            currency=Record::EUR;
            return;
        }
    default:
        return;
    }
}

QString Record::getCategory() const{
    return category;
}
QString Record::getDescription()const{
    return description;
}
