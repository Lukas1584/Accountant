#include "RecordsOperations.h"

RecordsOperations::RecordsOperations(std::shared_ptr<AbstractData>& data) : pData(data){
}

std::list<std::string> RecordsOperations::getCategories(const std::string& type) const{
    std::list<std::string> list;
    unsigned int rows=pData->rows();
    for(unsigned int i=0;i<rows;i++){
        RecordString rec=pData->getRecord(i);
        if(type==rec.getType()){
            std::string category=rec.getCategory();
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

std::list<std::string> RecordsOperations::getDescriptions(const std::string& category) const{
    std::list<std::string> list;
    unsigned int rows=pData->rows();
    for(unsigned int i=0;i<rows;i++){
        RecordString rec=pData->getRecord(i);
        if(category==rec.getCategory()){
            std::string description=rec.getDescription();
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

std::list<std::string> RecordsOperations::getCurrencies()const {
    std::list<std::string> list;
    unsigned int rows=pData->rows();
    for(unsigned int i=0;i<rows;i++){
        RecordString rec=pData->getRecord(i);
        std::string currency=rec.getCurrency();
        bool isUnique=true;
        for(const auto& j:list){
            if(j==currency)
                isUnique=false;
            }
            if(isUnique)
                list.push_back(currency);
    }
    list.sort();
    return list;
}
