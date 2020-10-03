#include "ReportSaveTxt.h"

ReportSaveTxt::ReportSaveTxt(const std::shared_ptr<Report> &rep)
    : pReport(rep){}

int ReportSaveTxt::stringLength(const std::string& str)const{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wstr=converter.from_bytes(str);
    return static_cast<int>(wstr.size());
}

void ReportSaveTxt::maxLengthFields(){
    fieldTypeLength=7; //size of "Прибыль"
    fieldCategoryLength=9; //size of "Категория"
    fieldDescriptionLength=8; //size of "Описание"
    fieldSumLength=5; //size of "Сумма"
    for(int i=0;i<pReport->rowsCount();i++){
        RecordString recordString=pReport->getRow(i);
        int sizeType=stringLength(recordString.getType());
        int sizeCategory=stringLength(recordString.getCategory());
        int sizeDescription=stringLength(recordString.getDescription());
        int sizeSum=stringLength(doubleToString(recordString.getSum()));
        if(fieldTypeLength<sizeType)
            fieldTypeLength=sizeType;
        if(fieldCategoryLength<sizeCategory)
            fieldCategoryLength=sizeCategory;
        if(fieldDescriptionLength<sizeDescription)
            fieldDescriptionLength=sizeDescription;
        if(fieldSumLength<sizeSum)
            fieldSumLength=sizeSum;
    }
}

std::string ReportSaveTxt::row(const int row)const{
    char separatorFields=' ';
    int numberSeparatorFields=1;
    std::string result;
    if(row==-1){
        result="Дата       ";
        std::string separatorType(fieldTypeLength-stringLength("Тип")+numberSeparatorFields,separatorFields);
        std::string separatorCategory(fieldCategoryLength-stringLength("Категория")+numberSeparatorFields,separatorFields);
        std::string separatorDescription(fieldDescriptionLength-stringLength("Описание")+numberSeparatorFields,separatorFields);
        std::string separatorSum(fieldSumLength-stringLength("Сумма")+numberSeparatorFields,separatorFields);
        result+="Тип"+separatorType+
                "Категория"+separatorCategory+
                "Описание"+separatorDescription+
                "Сумма"+separatorSum+
                "Валюта\n";
        return result;
    }
    RecordString recordString=pReport->getRow(row);
    result+=recordString.getDate()+separatorFields;
    std::string separatorType(fieldTypeLength-stringLength(recordString.getType())+numberSeparatorFields,separatorFields);
    std::string separatorCategory(fieldCategoryLength-stringLength(recordString.getCategory())+numberSeparatorFields,separatorFields);
    std::string separatorDescription(fieldDescriptionLength-stringLength(recordString.getDescription())+numberSeparatorFields,separatorFields);
    std::string separatorSum(fieldSumLength-stringLength(doubleToString(recordString.getSum()))+numberSeparatorFields,separatorFields);
    result+=recordString.getType()+separatorType+
            recordString.getCategory()+separatorCategory+
            recordString.getDescription()+separatorDescription+
            doubleToString(recordString.getSum())+separatorSum+
            recordString.getCurrency()+"\n";
    return result;
}

std::string ReportSaveTxt::doubleToString(const double value)const{
    std::stringstream ss;
    std::string string;
    ss<<value;
    ss>>string;
    return string;
}

void ReportSaveTxt::saveTxt(const std::string& filename,
                          const std::string& userName,
                          const std::string& currentDate){
    std::ofstream file{filename};
    file<<headerReport(userName,currentDate);
    maxLengthFields();
    for(int i=-1;i<pReport->rowsCount();i++)
        file<<row(i);
}

std::string ReportSaveTxt::headerReport(const std::string& userName,const std::string& currentDate) const{
    std::string type;
    if((pReport->getType().first==true)&&(pReport->getType().second==false)) type="Прибыль";
    if((pReport->getType().first==false)&&(pReport->getType().second==true)) type="Убыток";
    if((pReport->getType().first==true)&&(pReport->getType().second==true)) type="Все";
    return "Отчет\nПользователь:"+userName+"\tДата отчета:"+currentDate+"\nФильтр\n"+
            "Дата от:"+pReport->getDateFrom()+"\tДата до:"+pReport->getDateTo()+
            "\nТип:"+type+
            "\nСумма от:"+doubleToString(pReport->getSumFrom())+" Сумма до:"+doubleToString(pReport->getSumTo())+
            "\nКатегории:\n"+stringFromVector(pReport->getCategory())+
            "Описания:\n"+stringFromVector(pReport->getDescription())+
            "Валюты:\n"+stringFromVector(pReport->getCurrency())+"\n";
}

std::string ReportSaveTxt::stringFromVector(const std::vector<std::string>& vec)const{
    std::string result;
    if(vec[0]=="Все") return vec[0]+"\n";
    else{
        for(auto i:vec)
            result+=i+"\n";
        return result;
    }
}


