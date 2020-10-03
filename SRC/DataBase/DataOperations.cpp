#include "DataOperations.h"

void DataFileOperations::saveToFile(const std::string& fileName)const{
    std::ofstream file{fileName,std::ios_base::binary};
    for(int i=0;i<pData->rows();++i)
        save(file,pData->getRecord(i));
}

void DataFileOperations::loadFromFile(const std::string& fileName){
    int i=0;
    std::ifstream file{fileName,std::ios_base::binary};
    while(!file.eof()){
        Record rec=load(file);
        if(rec.getDate()!="")
            pData->setRecord(i,rec.convertToString());
        i++;
    }
}

Record DataFileOperations::load(std::istream& dataStream){
    Record record;
    char c;
    std::string tmp;
    while(dataStream.get(c) && c!=separatorRecord){
        tmp += c;
    }
    record.setDate(tmp);

    int typeInt=0;
    dataStream>>typeInt;
    if(typeInt==static_cast<int>(Record::Type::PROFIT))
        record.setType(Record::Type::PROFIT);
    if(typeInt==static_cast<int>(Record::Type::LOSS))
        record.setType(Record::Type::LOSS);

    tmp="";
    dataStream.get(c); //separatorRecord
    while(dataStream.get(c) && c!=separatorRecord){
        tmp += c;
    }
    record.setCategory(tmp);
    tmp="";
    while(dataStream.get(c) && c!=separatorRecord){
        tmp += c;
    }
    record.setDescription(tmp);

    double sum=0;
    dataStream>>sum;
    record.setSum(sum);
    dataStream.get(c); //separatorRecord

    int currencyInt=0;
    dataStream>>currencyInt;
    record.setCurrency(static_cast<Record::Currency>(currencyInt));
    dataStream.get(c); // '\n'
    return record;
}

void DataFileOperations::save(std::ostream& dataStream,const Record& record)const{
    dataStream<<record.getDate()<<separatorRecord;
    dataStream<<static_cast<int>(record.getType())<<separatorRecord;
    dataStream<<record.getCategory()<<separatorRecord;
    dataStream<<record.getDescription()<<separatorRecord;
    dataStream<<record.getSum()<<separatorRecord;
    dataStream<<static_cast<int>(record.getCurrency())<<'\n';
}
