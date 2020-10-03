#include "ReportSavePdf.h"

ReportSavePdf::ReportSavePdf(const std::shared_ptr<Report> &rep)
    : pReport(rep){
}

std::string ReportSavePdf::doubleToString(const double value)const{
    std::stringstream ss;
    std::string string;
    ss<<value;
    ss>>string;
    return string;
}

void ReportSavePdf::savePDF(const std::string& filename,
                          const std::string& userName,
                          const std::string& currentDate){
    /* creating and settings pdf*/
    HPDF_Doc pdf=HPDF_New(NULL,NULL);
    HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);
    HPDF_UseUTFEncodings(pdf);
    HPDF_SetCurrentEncoder(pdf, encoding);
    const char* fontName = HPDF_LoadTTFontFromFile (pdf, pathFont, HPDF_TRUE);
    font = HPDF_GetFont (pdf, fontName,encoding);

    newPage(pdf);
    HPDF_REAL yPosition=reportHeader(userName,currentDate,pdf);
    report(pdf,yPosition);

    HPDF_SaveToFile (pdf, filename.c_str());
    HPDF_Free (pdf);
}

void ReportSavePdf::printVector(const std::vector<std::string>& vec,
                                std::string& str,
                                HPDF_REAL& yPosition,
                                HPDF_Doc& pdf){
    HPDF_Page page=HPDF_GetCurrentPage(pdf);
    if(vec[0]=="Все") {
        if(yPosition<verticalBorder){
            page = newPage(pdf);
            yPosition=pageHeight-verticalBorder-leading;
        }
        str+="все";
        HPDF_Page_BeginText (page);
        HPDF_Page_TextOut (page,leftBorder,yPosition,str.c_str());
        HPDF_Page_EndText (page);
        yPosition-=leading;
        return;
    }
    HPDF_Page_BeginText (page);
    HPDF_Page_TextOut (page,leftBorder,yPosition,str.c_str());
    yPosition-=leading;
    for(auto i:vec){
        if(yPosition<verticalBorder){
            HPDF_Page_EndText (page);
            page = newPage(pdf);
            yPosition=pageHeight-verticalBorder-leading;
            HPDF_Page_BeginText (page);
        }
        HPDF_Page_TextOut (page,leftBorder+leading,yPosition,i.c_str());
        yPosition-=leading;
    }
    HPDF_Page_EndText (page);
    return;
}

HPDF_Page ReportSavePdf::newPage(HPDF_Doc& pdf){
    HPDF_Page page = HPDF_AddPage (pdf);
    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    HPDF_Page_SetFontAndSize (page, font, fontSize);
    HPDF_Page_SetTextLeading(page,leading);
    pageWidth=HPDF_Page_GetWidth(page);
    pageHeight=HPDF_Page_GetHeight(page);
    calculateParameters(pageWidth,pageHeight);
    return page;
}

HPDF_REAL ReportSavePdf::reportHeader(const std::string& userName,const std::string& currentDate,HPDF_Doc& pdf){
    HPDF_Page page=HPDF_GetCurrentPage(pdf);
    HPDF_Page_BeginText (page);
    HPDF_REAL yPosition=pageHeight-verticalBorder-leading;

    HPDF_REAL tw=HPDF_Page_TextWidth(page,"Отчет");
    HPDF_Page_TextOut (page,(pageWidth-tw+leftBorder-rightBorder)/2,yPosition,"Отчет");
    yPosition-=leading;

    std::string str="Пользователь: "+userName;
    HPDF_Page_TextOut (page,leftBorder,yPosition,str.c_str());
    yPosition-=leading;

    str="Дата отчета: "+currentDate;
    HPDF_Page_TextOut (page,leftBorder,yPosition,str.c_str());
    yPosition-=leading;

    tw=HPDF_Page_TextWidth(page,"Установки фильтра");
    HPDF_Page_TextOut (page,(pageWidth-tw+leftBorder-rightBorder)/2,yPosition,"Установки фильтра");
    yPosition-=leading;

    str="Дата от: "+pReport->getDateFrom()+"    Дата до: "+pReport->getDateTo();
    HPDF_Page_TextOut (page,leftBorder,yPosition,str.c_str());
    yPosition-=leading;

    str="Тип: ";
    if((pReport->getType().first==true)&&(pReport->getType().second==false)) str+="Прибыль";
    if((pReport->getType().first==false)&&(pReport->getType().second==true)) str+="Убыток";
    if((pReport->getType().first==true)&&(pReport->getType().second==true)) str+="все";
    HPDF_Page_TextOut (page,leftBorder,yPosition,str.c_str());
    yPosition-=leading;

    str="Сумма от: "+doubleToString(pReport->getSumFrom())+" Сумма до: "+doubleToString(pReport->getSumTo());
    HPDF_Page_TextOut (page,leftBorder,yPosition,str.c_str());
    yPosition-=leading;

    HPDF_Page_EndText (page);

    str="Валюты: ";
    printVector(pReport->getCurrency(),str,yPosition,pdf);

    str="Категории: ";
    printVector(pReport->getCategory(),str,yPosition,pdf);

    str="Описания: ";
    printVector(pReport->getDescription(),str,yPosition,pdf);
    return yPosition;
}

void ReportSavePdf::report(HPDF_Doc& pdf, HPDF_REAL& yPosition){
    HPDF_Page page=HPDF_GetCurrentPage(pdf);
    HPDF_Page_BeginText (page);
    tableHeader(page,yPosition);
    for(int row=0;row<pReport->rowsCount();++row){
        if(yPosition<verticalBorder){
            HPDF_Page_EndText (page);
            page = newPage(pdf);
            yPosition=pageHeight-verticalBorder-leading;
            HPDF_Page_BeginText (page);
            tableHeader(page,yPosition);
        }
        RecordString recordString=pReport->getRow(row);
        HPDF_Page_TextOut (page,leftBorder,yPosition,recordString.getDate().c_str());
        HPDF_Page_TextOut (page,xType,yPosition,recordString.getType().c_str());
        HPDF_Page_TextOut (page,xCategory,yPosition,recordString.getCategory().c_str());
        HPDF_Page_TextOut (page,xDescription,yPosition,recordString.getDescription().c_str());
        HPDF_Page_TextOut (page,xSum,yPosition,doubleToString(recordString.getSum()).c_str());
        HPDF_Page_TextOut (page,xCurrency,yPosition,recordString.getCurrency().c_str());
        yPosition-=leading;
    }
    HPDF_Page_EndText (page);
}

void ReportSavePdf::tableHeader(const HPDF_Page &page, HPDF_REAL& yPosition)const{
    HPDF_Page_TextOut (page,leftBorder,yPosition,"Дата");
    HPDF_Page_TextOut (page,xType,yPosition,"Тип");
    HPDF_Page_TextOut (page,xCategory,yPosition,"Категория");
    HPDF_Page_TextOut (page,xDescription,yPosition,"Описание");
    HPDF_Page_TextOut (page,xSum,yPosition,"Сумма");
    HPDF_Page_TextOut (page,xCurrency,yPosition,"Валюта");
    yPosition-=leading;
}

void ReportSavePdf::calculateParameters(const HPDF_REAL& pageWidth,const HPDF_REAL& pageHeight){
    leftBorder=static_cast<HPDF_REAL>(kLeftBorder*pageWidth);
    rightBorder=static_cast<HPDF_REAL>(kRightBorder*pageWidth);
    xType=static_cast<HPDF_REAL>(0.24*pageWidth);
    xCategory=static_cast<HPDF_REAL>(0.35*pageWidth);
    xDescription=static_cast<HPDF_REAL>(0.56*pageWidth);
    xSum=static_cast<HPDF_REAL>(0.78*pageWidth);
    xCurrency=static_cast<HPDF_REAL>(0.88*pageWidth);
    verticalBorder=static_cast<HPDF_REAL>(kVerticalBorder*pageHeight);
}
