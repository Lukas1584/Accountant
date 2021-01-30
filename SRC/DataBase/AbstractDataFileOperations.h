#pragma once
#include <string>

class AbstractDataFileOperations{
public:
    virtual void saveToFile(std::string fileName)const=0;
    virtual void loadFromFile(std::string fileName)=0;
    virtual void deleteFile(std::string fileName)=0;
};
