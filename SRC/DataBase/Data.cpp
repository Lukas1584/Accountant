#include "Data.h"

Data::Data(){}

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

int Data::rows(){
    return data.size();
}

int Data::columns(){
    return data[0].columns();
}

QVariant Data::at(int column,int row){
    return QVariant(data[row].convert(column));
}

void Data::remove(int row){
    data.erase(data.begin()+row);
}

void Data::insertRows(int row,int count){
    Record rec;
    for (int i=0;i<count;i++)
        data.insert(data.begin()+row,rec);
}

void Data::setData(int row,int column,QVariant value){
    data[row].setData(column,value);
}

QStringList Data::getCategories(const QString& type){
    QStringList categories;
    for(auto i:data){
        if(i.convert(1).toString()==type){
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

QStringList Data::getDescriprions(const QString& category){
    QStringList descroptions;
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
