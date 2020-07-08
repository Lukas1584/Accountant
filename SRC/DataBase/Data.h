#pragma once
#include <vector>
#include "SRC/DataBase/Record.h"
#include <list>
#include <iostream>
#include <algorithm>

class Data
{
public:
    Data();
    void clear();
    int rows()const;
    int columns()const;
    void remove(const int row);
    void insertRows(const int row,const int count=1);
    void setData(const int row,const int column,const std::string& value);
    void sort();
    std::string at(const int row,const int column)const;
    float getSum(const int row)const;

    friend std::istream& operator>>(std::istream& dataStream, Data& rhs);
    friend std::ostream& operator<<(std::ostream& dataStream,const Data& rhs);

private:
    std::vector<Record> data;
};


