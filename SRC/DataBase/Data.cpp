#include "Data.h"

Data::Data()
{

}
void Data::add(Record& record){
    data.push_back(record);
}

std::vector<Record> Data::getData(){
    std::vector<Record> d=data;
    return d;
}

QDataStream& operator>>(QDataStream& dataStream, Data* rhs){
    while(!dataStream.atEnd()){
        Record i;
        dataStream>>i;
        rhs->data.push_back(i);
    }
    return dataStream;
}

QDataStream& operator<<(QDataStream& dataStream, Data* rhs){
    for(auto i:rhs->data){
        dataStream<<i;
    }
    return dataStream;
}

void Data::clear(){
    data.clear();
}
