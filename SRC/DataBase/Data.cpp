#include "Data.h"

void Data::clear(){
    data.clear();
}

int Data::rows()const{
    return static_cast<int> (data.size());
}

int Data::columns()const{
    Record temp;
    return temp.columns();
}

void Data::remove(const int row){
    data.erase(data.begin()+row);
}

void Data::sort(){
    std::sort(data.begin(),data.end());
}

const RecordString Data::getRecord(const int row)const{
    return data[row].convertToString();
}

void Data::setRecord(const int row,const RecordString& record){
    if(row > static_cast<int>(data.size())-1)
        data.push_back(record);
    else data[row]=record;
}
std::list<std::string> Data::getAllCurrencies() const{
    Record rec;
    return rec.getAllCurrencies();
}

std::list<std::string> Data::getAllTypes()const{
    Record rec;
    return rec.getAllTypes();
}
