#pragma once
#include <string>

class AbstractDataFileOperations{
public:
    virtual void saveToFile(const std::string& fileName)=0;
    virtual void loadFromFile(const std::string& fileName)=0;
};
