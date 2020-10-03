#include "BalanceCalculator.h"

BalanceCalculator::BalanceCalculator(std::shared_ptr<AbstractData>& data,std::shared_ptr<RecordsOperations>& operations):
    pData(data),pOperations(operations){}

std::string BalanceCalculator::balance(const BalanceCalculator::Time period, const std::string& currency)const{
    std::string balance;
    if(period==BalanceCalculator::Time::allTime)
       balance=balanceCalculate(pData->getRecord(0).getDate(),currency);
    if(period==BalanceCalculator::Time::year)
       balance=balanceCalculate(minusYear(),currency);
    if(period==BalanceCalculator::Time::month)
        balance=balanceCalculate(minusMonth(),currency);
    return balance;
}

std::string BalanceCalculator::minusYear() const{
    std::stringstream ss;
    ss<<currentDate.substr(0,4);
    int currentYear;
    ss>>currentYear;
    currentYear--;
    ss.clear();
    ss<<currentYear;
    std::string dateMinusYear;
    ss>>dateMinusYear;
    dateMinusYear+=currentDate.substr(4,6);
    return dateMinusYear;
}

std::string BalanceCalculator::balanceCalculate(const std::string& dateFrom,const std::string& currency)const{
    double balanceDouble=0;
    for(int i=0;i<pData->rows();i++){
        RecordString rec=pData->getRecord(i);
        std::string date=rec.getDate();
        if((dateFrom<=date && date<=currentDate)&&(currency==rec.getCurrency())){
            if(rec.getType()==profit)
                balanceDouble+=rec.getSum();
            if(rec.getType()==loss)
                balanceDouble-=rec.getSum();
        }
    }
    std::string balance;
    std::stringstream ss;
    ss<<balanceDouble;
    ss>>balance;
    return balance;
}

std::string BalanceCalculator::minusMonth()const{
    std::stringstream ss;
    ss<<currentDate.substr(5,2);
    int currentMonth;
    ss>>currentMonth;
    if(currentMonth==1)
        currentMonth=12;
    else currentMonth--;
    ss.clear();
    ss<<currentMonth;
    std::string str;
    ss>>str;
    if(str.size()==1)
        str.insert(0,"0");
    return currentDate.substr(0,5)+str+currentDate.substr(7,3);
}

std::string BalanceCalculator::getBalance(const std::string &date){
    currentDate=date;
    std::list<std::string> list=pOperations->getCurrencies();
    std::string result="Баланс за месяц:\n\n";
    for(const auto& i:list)
        result+=i+": "+balance(BalanceCalculator::Time::month,i)+"\n";
    result+="\nБаланс за год:\n\n";
    for(const auto& i:list)
        result+=i+": "+balance(BalanceCalculator::Time::year,i)+"\n";
    result+="\nБаланс за все время:\n\n";
        for(const auto& i:list)
            result+=i+": "+balance(BalanceCalculator::Time::allTime,i)+"\n";
    return result;
}
