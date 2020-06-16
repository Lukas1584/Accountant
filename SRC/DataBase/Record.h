#pragma once
#include <QString>
#include <QDate>

class Record{

public:
    int id;
    QDate date;
    enum Type{
        PROFIT=1, LOSS
    }type;
    QString category;
    QString description;
    float sum;
    enum Currency{
        USD=1, BYR, RUB, EUR
    }currency;
};

QDataStream& operator>>(QDataStream& dataStream, Record& rhs);
QDataStream& operator<<(QDataStream& dataStream, const Record& rhs);
