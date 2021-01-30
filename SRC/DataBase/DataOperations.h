#pragma once
#include <fstream>
#include <memory>
#include <string>
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/AbstractDataFileOperations.h"

class DataFileOperations: public AbstractDataFileOperations{
public:
    explicit DataFileOperations(std::shared_ptr<AbstractData> data):pData(data){}

    void saveToFile(std::string fileName)const override;
    void loadFromFile(std::string fileName) override;
    void deleteFile(std::string fileName) override;
private:
    std::shared_ptr<AbstractData> pData;
    const char separatorRecord='~';

    void save(std::ofstream& dataStream,const Record&) const;
    Record load(std::ifstream& dataStream);
};

