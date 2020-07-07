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

std::string Data::at(const int column, const int row) const{
    return data[row].convert(column);
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

std::list<std::string> Data::getCategories(const std::string &type) const{
    std::list<std::string> categories;
    for(auto i:data){
        if(i.convert(1)==type){
            bool isCategoryOnList=false;
            for(auto k:categories){
                if(k==i.getCategory())
                    isCategoryOnList=true;
            }
            if (!isCategoryOnList)
                categories.push_back(i.getCategory());
        }
    }
    categories.sort();
    return categories;
}

std::list<std::string> Data::getDescriprions(const std::string& category) const{
    std::list<std::string> descroptions;
    for(auto i:data){
        if(i.getCategory()==category){
            bool isDescriptionOnList=false;
            for(auto k:descroptions){
                if(k==i.getDescription())
                    isDescriptionOnList=true;
            }
            if (!isDescriptionOnList)
                descroptions.push_back(i.getDescription());
        }
    }
    descroptions.sort();
    return descroptions;
}

void Data::sort(){
    std::sort(data.begin(),data.end());
}
