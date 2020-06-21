#pragma once
#include<vector>
#include "SRC/DataBase/Record.h"
#include <QDataStream>
#include <QVariant>

class Data
{
public:
    Data();
    void add(Record& record);
    std::vector<Record> getData();
    void clear();
    int rows();
    int columns();
    void remove(int row);
    void insertRows(int row,int count=1);
    void setData(int row,int column,QVariant value);
    QStringList getCategories(const QString& type);
    QStringList getDescriprions(const QString& category);

    friend QDataStream& operator>>(QDataStream& dataStream, Data* rhs);
    friend QDataStream& operator<<(QDataStream& dataStream, Data* rhs);

    QVariant at(int column,int row);

private:
    std::vector<Record> data;
};


