#pragma once
#include <string>
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/Record.h"
#include <fstream>
#include <locale>
#include <codecvt>
#include "SRC/BusinessLogic/Record_String.h"

class Report_Save{
public:
    Report_Save(const std::shared_ptr<Data>& data,const std::vector<bool>& fil);
    void saveTxt(const std::string& filename);
private:
    std::shared_ptr<Data> pData;
    std::vector<bool> filter;
    int fieldTypeLength=0;
    int fieldCategoryLength=0;
    int fieldDescriptionLength=0;
    int fieldSumLength=0;

    int stringLength(const std::string& str)const;
    std::string row(const int row)const;
    void maxLength();
};

