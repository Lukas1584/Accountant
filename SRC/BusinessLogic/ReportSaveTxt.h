#pragma once
#include <string>
#include <fstream>
#include <codecvt>
#include "SRC/BusinessLogic/Report.h"
#include "SRC/BusinessLogic/RecordString.h"
#include <sstream>
#include <wchar.h>

class ReportSaveTxt{
public:
    ReportSaveTxt(const std::shared_ptr<Report>& rep);
    void saveTxt(const std::string& filename,
                 const std::string& userName,
                 const std::string& currentDate);

private:

    std::shared_ptr<Report> pReport;
    int fieldTypeLength=0;
    int fieldCategoryLength=0;
    int fieldDescriptionLength=0;
    int fieldSumLength=0;

    int stringLength(const std::string& str)const;
    std::string row(const int row)const;
    void maxLengthFields();
    std::string doubleToString(const double value)const;
    std::string headerReport(const std::string& userName,const std::string& currentDate)const;
    std::string stringFromVector(const std::vector<std::string>& vec)const;
};

