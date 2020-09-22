#include "Balance_Calculator.h"
constexpr int year=0;
constexpr int month=1;
constexpr char LOSS[]="Убыток";
constexpr char PROFIT[]="Прибыль";

Balance_Calculator::Balance_Calculator(std::shared_ptr<AbstractData>& data,std::shared_ptr<Records_Operations>& operations):
    pData(data),pOperations(operations){}

std::string Balance_Calculator::balance(const int period, const std::string& currency)const{
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
    double balanceDouble=0;
    for(int i=0;i<pData->rows();i++){
        Record_String rec=pData->getRecord(i);
        std::string date=rec.getDate();
        if((dateFrom<=date && date<=currentDate)&&(currency==rec.getCurrency())){
            if(rec.getType()==PROFIT)
                balanceDouble+=rec.getSum();
            if(rec.getType()==LOSS)
                balanceDouble-=rec.getSum();
        }
    }
    std::string balance;
    std::stringstream ss;
    ss<<balanceDouble;
    ss>>balance;
    return balance;
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

std::string Balance_Calculator::getBalance(const std::string &date){
    currentDate=date;
    std::list<std::string> list=pOperations->getCurrencies();
    std::string result="Баланс за месяц:\n\n";
    for(const auto& i:list)
        result+=i+": "+balance(month,i)+"\n";
    result+="\nБаланс за год:\n\n";
    for(const auto& i:list)
        result+=i+": "+balance(year,i)+"\n";
    return result;
}
