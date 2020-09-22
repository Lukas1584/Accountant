#pragma once
#include "SRC/DataBase/AbstractData.h"
#include <vector>
#include <algorithm>
#include "SRC/DataBase/Record.h"

class Data:public AbstractData{
public:
    int rows()const override;
    int columns()const override;
    void remove(const int row) override;
    void sort() override;
    const Record_String getRecord(const int row) override;
    void setRecord(const int row,const Record_String& record) override;
    void clear()override;
    std::list<std::string> getAllCurrencies()override;
    std::list<std::string> getAllTypes()override;
private:
    std::vector<Record> data;
};


