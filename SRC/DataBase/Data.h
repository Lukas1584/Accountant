#pragma once
#include<vector>
#include "SRC/DataBase/Record.h"
#include <QDataStream>







class Data
{
public:

    Data();
    void add(Record& record);
    std::vector<Record> getData();
    void clear();

    friend QDataStream& operator>>(QDataStream& dataStream, Data* rhs);
    friend QDataStream& operator<<(QDataStream& dataStream, Data* rhs);

private:
    std::vector<Record> data;
};


