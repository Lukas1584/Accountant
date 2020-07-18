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

void Data::remove(const int row){
    data.erase(data.begin()+row);
}

void Data::sort(){
    std::sort(data.begin(),data.end());
}

Record Data::getRecord(const int row){
    return data[row];
}

void Data::setRecord(const int row,const Record& record){
    if(row > static_cast<int>(data.size())-1)
        data.push_back(record);
    else data[row]=record;
}
