#pragma once
#include <vector>
#include "SRC/DataBase/Record.h"
#include "SRC/BusinessLogic/Record_String.h"
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
    void sort();
    Record getRecord(const int row);
    void setRecord(const int row,const Record& record);

    friend std::istream& operator>>(std::istream& dataStream, Data& rhs);
    friend std::ostream& operator<<(std::ostream& dataStream,const Data& rhs);

private:
    std::vector<Record> data;
};


