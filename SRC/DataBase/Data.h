#pragma once
#include <vector>
#include <algorithm>
#include "SRC/DataBase/AbstractData.h"
#include "SRC/DataBase/Record.h"

class Data:public AbstractData{
public:
    unsigned int rows()const override;
    unsigned int columns()const override;
    void remove(const int row) override;
    void sort() override;
    const RecordString getRecord(const unsigned int row)const override;
    void setRecord(const unsigned int row,const RecordString& record) override;
    void clear()override;
private:
    std::vector<Record> data;
    std::list<std::string> getAllCurrencies()const override;
    std::list<std::string> getAllTypes()const override;
};
