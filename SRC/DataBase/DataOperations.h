#pragma once
#include "SRC/DataBase/AbstractDataFileOperations.h"
#include <iostream>
#include "SRC/DataBase/Data.h"
#include <fstream>

class DataFileOperations: public AbstractDataFileOperations{
public:
    explicit DataFileOperations(std::shared_ptr<AbstractData> data):pData(data){}

    void saveToFile(const std::string& fileName)const override;
    void loadFromFile(const std::string& fileName) override;
private:
    std::shared_ptr<AbstractData> pData;
    const char separatorRecord='~';

    void save(std::ostream& dataStream,const Record&) const;
    Record load(std::istream& dataStream);
};

