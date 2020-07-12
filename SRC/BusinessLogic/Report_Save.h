#pragma once
#include <string>
#include "SRC/DataBase/Data.h"
#include <fstream>
#include <locale>
#include <codecvt>

class Report_Save{
public:
    Report_Save(const std::shared_ptr<Data>& data,const std::vector<bool>& fil);
    void saveTxt(const std::string& filename);
private:
    std::shared_ptr<Data> pData;
    std::vector<bool> filter;

    int stringLength(const std::string& str)const;
    std::string row(const int row)const;
    int maxLength(const int column)const;
};

