#include "Record.h"
#include <QDataStream>

QDataStream& operator>>(QDataStream& dataStream, Record& rhs){
    dataStream>>rhs.id;
    dataStream>>rhs.date;
    dataStream>>rhs.type;
    dataStream>>rhs.category;
    dataStream>>rhs.description;
    dataStream>>rhs.sum;
    dataStream>>rhs.currency;
    return dataStream;
}

QDataStream& operator<<(QDataStream& dataStream,const Record& rhs){
    dataStream<<rhs.id;
    dataStream<<rhs.date;
    dataStream<<rhs.type;
    dataStream<<rhs.category;
    dataStream<<rhs.description;
    dataStream<<rhs.sum;
    dataStream<<rhs.currency;
    return dataStream;
}
