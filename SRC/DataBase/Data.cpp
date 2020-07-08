#include "Data.h"

Data::Data(){}

std::istream& operator>>(std::istream& dataStream, Data& rhs){
    while(!dataStream.eof()){
        Record i;
        dataStream>>i;
        if(i.isNotEmpty())
            rhs.data.push_back(i);
    }
    return dataStream;
}

std::ostream& operator<<(std::ostream& dataStream,const Data& rhs){
    for(auto i:rhs.data){
        dataStream<<i;
    }
    return dataStream;
}

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

std::string Data::at(const int row,const int column) const{
    return data[row].at(column);
}

void Data::remove(const int row){
    data.erase(data.begin()+row);
}

void Data::insertRows(const int row, const int count){
    Record rec;
    for (int i=0;i<count;i++)
        data.insert(data.begin()+row,rec);
}

void Data::setData(const int row, const int column, const std::string &value){
    data[row].setData(column,value);
}

void Data::sort(){
    std::sort(data.begin(),data.end());
}

float Data::getSum(const int row)const{
    return data[row].getSum();
}
