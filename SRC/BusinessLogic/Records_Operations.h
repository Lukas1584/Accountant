#pragma once
#include "SRC/DataBase/Data.h"
#include <list>

class Records_Operations{
public:
    explicit Records_Operations(std::shared_ptr<AbstractData> &data);
    std::list<std::string> getCategories(const std::string &type)const;
    std::list<std::string> getDescriptions(const std::string& category)const;
    std::list<std::string> getCurrencies() const;

private:
    std::shared_ptr<AbstractData> pData;
};











