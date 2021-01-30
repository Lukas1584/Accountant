#pragma once
#include "SRC/DataBase/Data.h"
#include "SRC/BusinessLogic/RecordString.h"
#include <list>
#include <memory>
#include <string>

class RecordsOperations{
public:
    explicit RecordsOperations(std::shared_ptr<AbstractData> &data);
    std::list<std::string> getCategories(const std::string &type)const;
    std::list<std::string> getDescriptions(const std::string& category)const;
    std::list<std::string> getCurrencies() const;

private:
    std::shared_ptr<AbstractData> pData;
};











