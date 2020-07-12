#include "Balance_Calculator.h"

Balance_Calculator::Balance_Calculator(std::shared_ptr<Data>& data, QObject *parent) : QObject (parent),pData(data){}

std::string Balance_Calculator::balance(const int period, const std::string &currency)const{
    std::string balance;
    if(period==year)
       balance=balanceCalculate(minusYear(),currency);
    if(period==month)
        balance=balanceCalculate(minusMonth(),currency);
    return balance;
}

std::string Balance_Calculator::minusYear() const{
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

std::string Balance_Calculator::balanceCalculate(const std::string& dateFrom,const std::string& currency)const{
    float balanceFloat=0;
    for(int i=0;i<pData->rows();i++){
        std::string date=pData->at(i,0);
        if((dateFrom<=date && date<=currentDate)&&(currency==pData->at(i,5))){
            if(pData->at(i,1)=="Прибыль")
                balanceFloat+=pData->getSum(i);
            if(pData->at(i,1)=="Убыток")
                balanceFloat-=pData->getSum(i);
        }
    }
    std::string balance;
    std::stringstream ss;
    ss<<balanceFloat;
    ss>>balance;
    return balance;
}

void Balance_Calculator::setCurrentDate(const std::string& date){
    currentDate=date;
}

std::string Balance_Calculator::minusMonth()const{
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

std::string Balance_Calculator::getBalance()const{
    return "Баланс за месяц:\n\n"+
            balance(month,"USD")+" USD\n"+
            balance(month,"BYR")+" BYR\n"+
            balance(month,"RUB")+" RUB\n"+
            balance(month,"EUR")+" EUR\n\n"+
            "Баланс за год:\n\n"+
            balance(year,"USD")+" USD\n"+
            balance(year,"BYR")+" BYR\n"+
            balance(year,"RUB")+" RUB\n"+
            balance(year,"EUR")+" EUR\n\n";
}
