#pragma once
#include<vector>
#include "SRC/DataBase/Record.h"
#include <QDataStream>
#include <QVariant>

class Data
{
public:
    Data();
    void add(const Record& record);
    std::vector<Record> getData() const;
    void clear();
    int rows()const;
    int columns()const;
    void remove(const int row);
    void insertRows(const int row,const int count=1);
    void setData(const int row,const int column,const QVariant& value);
    QStringList getCategories(const QString& type)const;
    QStringList getDescriprions(const QString& category)const;

    friend QDataStream& operator>>(QDataStream& dataStream, Data& rhs);
    friend QDataStream& operator<<(QDataStream& dataStream,const Data& rhs);

    QVariant at(const int column,const int row)const;

private:
    std::vector<Record> data;
};


