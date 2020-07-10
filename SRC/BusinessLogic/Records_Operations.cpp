#include "Records_Operations.h"

Records_Operations::Records_Operations(std::shared_ptr<Data>& data, QObject* pobj) : QObject(pobj),pData(data){
}

int Records_Operations::rowCount() const{
    return pData->rows();
}

int Records_Operations::columnCount() const{
    return pData->columns();
}

std::string Records_Operations::data(const int row,const int column) const{
    return pData->at(row,column);
}

void Records_Operations::insertRows(int row, int count){
    pData->insertRows(row,count);
}

void Records_Operations::removeRows(int row){
    pData->remove(row);
}

void Records_Operations::setData(const int row,const int column, const std::string& value){
    pData->setData(row,column,value);
    emit dataChanged();
}

void Records_Operations::sortData(){
    pData->sort();
}

std::list<std::string> Records_Operations::getCategoryOrDescription(const std::string& typeOrCategory,const std::string& type) const{
    std::list<std::string> list;
    int keyColumn;
    int dependentColumn;
    if(type=="category"){
        keyColumn=1;
        dependentColumn=2;
    }
    if(type=="description"){
        keyColumn=2;
        dependentColumn=3;
    }
    for(int i=0;i<rowCount();i++){
        std::string categoryOrDescriptionCheck=pData->at(i,keyColumn);
        if(typeOrCategory==categoryOrDescriptionCheck){
            std::string categoryOrDescription=pData->at(i,dependentColumn);
            bool isUnique=true;
            for(auto j:list){
                if(j==categoryOrDescription)
                    isUnique=false;
            }
            if(isUnique)
                list.push_back(categoryOrDescription);
        }
    }
    list.sort();
    return list;
}
