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
    std::list<std::string> getCategories(const std::string& type)const;
    std::list<std::string> getDescriprions(const std::string& category)const;

    friend std::istream& operator>>(std::istream& dataStream, Data& rhs);
    friend std::ostream& operator<<(std::ostream& dataStream,const Data& rhs);

    std::string at(const int column,const int row)const;
    void sort();

private:
    std::vector<Record> data;
};


