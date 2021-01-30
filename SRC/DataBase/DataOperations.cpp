#include "DataOperations.h"

void DataFileOperations::saveToFile(std::string fileName)const{
    fileName+=".dat";
    std::ofstream file{fileName};
    if(!file) throw "File wasn't created";
    unsigned int rows=pData->rows();
    for(unsigned int i=0;i<rows;++i)
        save(file,pData->getRecord(i));
}

void DataFileOperations::loadFromFile(std::string fileName){
    fileName+=".dat";
    std::ifstream file{fileName};
    if(!file) throw "File doesn't exist";
    int i=0;
    while(!file.eof()){
        Record rec=load(file);
        if(rec.getDate()!="")
            pData->setRecord(i,rec.convertToString());
        i++;
    }
}

Record DataFileOperations::load(std::ifstream& dataStream){
    Record record;
    char c;
    std::string tmp;
    //Date
    while(dataStream.get(c) && c!=separatorRecord){
        tmp += c;
    }
    record.setDate(tmp);
    //Type
    int typeInt=0;
    dataStream>>typeInt;
    if(typeInt==static_cast<int>(Record::Type::PROFIT))
        record.setType(Record::Type::PROFIT);
    if(typeInt==static_cast<int>(Record::Type::LOSS))
        record.setType(Record::Type::LOSS);
    dataStream.get(c); //separatorRecord
    //Category
    tmp.clear();
    while(dataStream.get(c) && c!=separatorRecord){
        tmp += c;
    }
    record.setCategory(tmp);
    //Description
    tmp.clear();
    while(dataStream.get(c) && c!=separatorRecord){
        tmp += c;
    }
    record.setDescription(tmp);
    //Sum
    double sum=0;
    dataStream>>sum;
    record.setSum(sum);
    dataStream.get(c); //separatorRecord
    //Currency
    int currencyInt=0;
    dataStream>>currencyInt;
    record.setCurrency(static_cast<Record::Currency>(currencyInt));
    dataStream.get(c); // '\n'
    return record;
}

void DataFileOperations::save(std::ofstream& dataStream,const Record& record)const{
    dataStream<<record.getDate()<<separatorRecord
              <<static_cast<int>(record.getType())<<separatorRecord
              <<record.getCategory()<<separatorRecord
              <<record.getDescription()<<separatorRecord
              <<record.getSum()<<separatorRecord
              <<static_cast<int>(record.getCurrency())<<'\n';
}

void DataFileOperations::deleteFile(std::string fileName){
    fileName+=".dat";
    std::remove(fileName.c_str());
}
