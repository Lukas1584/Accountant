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
