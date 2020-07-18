#include "Records_Operations.h"

Records_Operations::Records_Operations(std::shared_ptr<Data>& data, QObject* pobj) : QObject(pobj),pData(data){
}

int Records_Operations::rowCount() const{
    return pData->rows();
}

int Records_Operations::columnCount() const{
    return pData->columns();
}

void Records_Operations::removeRow(const int row){
    pData->remove(row);
}

void Records_Operations::sortData(){
    pData->sort();
}

Record_String Records_Operations::data(const int row) const{
    return pData->getRecord(row);
}

void Records_Operations::setData(const int row, const Record_String& rec){
    pData->setRecord(row,rec.convertToRecord());
}

std::list<std::string> Records_Operations::getCategory(const std::string& type) const{
    std::list<std::string> list;
    for(int i=0;i<rowCount();i++){
        Record rec=pData->getRecord(i);
        Record_String recString(rec);
        if(type==recString.getType()){
            std::string category=recString.getCategory();
            bool isUnique=true;
            for(const auto& j:list){
                if(j==category)
                    isUnique=false;
            }
            if(isUnique)
                list.push_back(category);
        }
    }
    list.sort();
    return list;
}

std::list<std::string> Records_Operations::getDescription(const std::string& category) const{
    std::list<std::string> list;
    for(int i=0;i<rowCount();i++){
        Record rec=pData->getRecord(i);
        Record_String recString(rec);
        if(category==recString.getCategory()){
            std::string description=recString.getDescription();
            bool isUnique=true;
            for(const auto& j:list){
                if(j==description)
                    isUnique=false;
            }
            if(isUnique)
                list.push_back(description);
        }
    }
    list.sort();
    return list;
}
