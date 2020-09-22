#pragma once
#include "SRC/DataBase/Data.h"
#include "SRC/BusinessLogic/Record_String.h"
#include "SRC/BusinessLogic/Records_Operations.h"
#include <list>

class Balance_Calculator{

public:
    Balance_Calculator(std::shared_ptr<AbstractData>& data,std::shared_ptr<Records_Operations>& operations);
    std::string getBalance(const std::string& date);

private:
    std::shared_ptr<AbstractData> pData;
    std::shared_ptr<Records_Operations> pOperations;
    std::string currentDate;

    std::string balance(const int period, const std::string& currency)const;
    std::string minusYear()const;
    std::string minusMonth()const;
    std::string balanceCalculate(const std::string& dateFrom, const std::string &currency)const;
};


