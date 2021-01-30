#include "Data.h"

void Data::clear(){
    data.clear();
}

unsigned int Data::rows()const{
    return data.size();
}

unsigned int Data::columns()const{
    Record temp;
    return temp.columns();
}

void Data::remove(const int row){
    data.erase(data.begin()+row);
}

void Data::sort(){
    std::sort(data.begin(),data.end());
}

const RecordString Data::getRecord(const unsigned int row)const{
    return data[row].convertToString();
}

void Data::setRecord(const unsigned int row,const RecordString& record){
    if((row+1)>data.size())
        data.push_back(record);
    else data[row]=record;
}

std::list<std::string> Data::getAllCurrencies()const{
    Record rec;
    return rec.getAllCurrencies();
}

std::list<std::string> Data::getAllTypes()const{
    Record rec;
    return rec.getAllTypes();
}
