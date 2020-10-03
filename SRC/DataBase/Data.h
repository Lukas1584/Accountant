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
    const RecordString getRecord(const int row)const override;
    void setRecord(const int row,const RecordString& record) override;
    void clear()override;
    std::list<std::string> getAllCurrencies()const override;
    std::list<std::string> getAllTypes()const override;
private:
    std::vector<Record> data;
};


