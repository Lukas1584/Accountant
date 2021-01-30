#pragma once
#include "SRC/DataBase/Data.h"
#include "SRC/BusinessLogic/RecordString.h"
#include "SRC/BusinessLogic/RecordsOperations.h"
#include <list>
#include <memory>

class BalanceCalculator{

public:
    BalanceCalculator(std::shared_ptr<AbstractData>& data,std::shared_ptr<RecordsOperations>& operations);
    std::string getBalance(const std::string& date);

private:
    std::shared_ptr<AbstractData> pData;
    std::shared_ptr<RecordsOperations> pOperations;
    std::string currentDate;

    enum class Time{
        year,month,allTime
    };
    const char* loss="Убыток";
    const char* profit="Прибыль";

    std::string balance(const BalanceCalculator::Time period, const std::string& currency)const;
    std::string minusYear()const;
    std::string minusMonth()const;
    std::string balanceCalculate(const std::string& dateFrom, const std::string &currency)const;
};
