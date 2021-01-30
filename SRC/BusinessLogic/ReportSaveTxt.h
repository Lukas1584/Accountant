#pragma once
#include <wchar.h>
#include <string>
#include <fstream>
#include <codecvt>
#include "SRC/BusinessLogic/Report.h"
#include "SRC/BusinessLogic/RecordString.h"
#include <sstream>
#include <locale>

class ReportSaveTxt{
public:
    ReportSaveTxt(const std::shared_ptr<Report>& rep);
    void saveTxt(const std::string& filename,
                 const std::string& userName,
                 const std::string& currentDate);

private:
    std::shared_ptr<Report> pReport;
    int fieldTypeLength=7; //size of "Прибыль"
    int fieldCategoryLength=9; //size of "Категория"
    int fieldDescriptionLength=8; //size of "Описание"
    int fieldSumLength=5; //size of "Сумма"

    int stringLength(const std::string& str)const;
    std::string row(const int row)const;
    void maxLengthFields();
    std::string doubleToString(const double value)const;
    std::string headerReport(const std::string& userName,const std::string& currentDate)const;
    std::string stringFromVector(const std::vector<std::string>& vec)const;
};

