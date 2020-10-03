#pragma once
#include <string>
#include "SRC/BusinessLogic/Report.h"
#include "SRC/BusinessLogic/RecordString.h"
#include <sstream>
#include <hpdf.h>

class ReportSavePdf{
public:
    ReportSavePdf(const std::shared_ptr<Report>& rep);
    void savePDF(const std::string& filename,
                 const std::string& userName,
                 const std::string& currentDate);
private:
    std::shared_ptr<Report> pReport;

    std::string doubleToString(const double value)const;
    void printVector(const std::vector<std::string>& vec, std::string& str, HPDF_REAL& yPosition, HPDF_Doc &pdf);
    HPDF_REAL reportHeader(const std::string& userName, const std::string& currentDate, HPDF_Doc& pdf);
    void report(HPDF_Doc& pdf, HPDF_REAL& yPos);
    void tableHeader(const HPDF_Page& page,HPDF_REAL& yPosition)const;
    void calculateParameters(const HPDF_REAL& pageWidth, const HPDF_REAL &pageHeight);
    HPDF_Page newPage(HPDF_Doc& pdf);

    const HPDF_REAL leading=20;
    const double kLeftBorder=0.12;
    const double kRightBorder=0.024;
    const double kVerticalBorder=0.017;
    const char* pathFont="fonts/arial.ttf";
    const char* encoding="UTF-8";
    const HPDF_REAL fontSize=12;
    HPDF_Font font;
    HPDF_REAL pageWidth;
    HPDF_REAL pageHeight;
    HPDF_REAL leftBorder;
    HPDF_REAL rightBorder;
    HPDF_REAL verticalBorder;
    HPDF_REAL xType;
    HPDF_REAL xCategory;
    HPDF_REAL xDescription;
    HPDF_REAL xSum;
    HPDF_REAL xCurrency;
};





