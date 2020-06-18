#pragma once
#include <QString>
#include <QDate>
#include <QVariant>
#include <QDataStream>

class Record{

public:
    QVariant convert(const int column);
    int columns();

    friend QDataStream& operator>>(QDataStream& dataStream, Record& rhs);
    friend QDataStream& operator<<(QDataStream& dataStream, const Record& rhs);

private:
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


