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

QVariant Record::convert(int column){
    switch (column){
    case 0:
        return QVariant(date.toString("dd.MM.yyyy"));
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
int Record::columns()
{
    return 6;
}


