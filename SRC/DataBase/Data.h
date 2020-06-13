#pragma once
#include<vector>
#include "SRC/DataBase/Record.h"


class Data
{
public:

    Data();
    void add(Record& record);
    std::vector<Record> getData();
private:
    std::vector<Record> data;
};


