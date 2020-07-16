#include "Report_Save.h"

Report_Save::Report_Save(const std::shared_ptr<Data>& data,const std::vector<bool>& fil)
    : pData(data),filter(fil){}

void Report_Save::saveTxt(const std::string& filename){
    std::ofstream file{filename};
    maxLength();
    for(int i=0;i<static_cast<int>(filter.size());i++){
        if(filter[i]){
            file<<row(i);
        }
    }
}

int Report_Save::stringLength(const std::string& str)const{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wstr=converter.from_bytes(str);
    return static_cast<int>(wstr.size());
}

void Report_Save::maxLength(){
    int maxType=0;
    int maxCategory=0;
    int maxDescription=0;
    int maxSum=0;
    for(int i=0;i<static_cast<int>(filter.size());i++){
        if(filter[i]){
            Record record=pData->getRecord(i);
            Record_String recordString(record);
            int sizeType=stringLength(recordString.getType());
            int sizeCategory=stringLength(recordString.getCategory());
            int sizeDescription=stringLength(recordString.getDescription());
            int sizeSum=stringLength(recordString.getSum());
            if(maxType<sizeType)
                maxType=sizeType;
            if(maxCategory<sizeCategory)
                maxCategory=sizeCategory;
            if(maxDescription<sizeDescription)
                maxDescription=sizeDescription;
            if(maxSum<sizeSum)
                maxSum=sizeSum;
        }
    }
    fieldTypeLength=maxType;
    fieldCategoryLength=maxCategory;
    fieldDescriptionLength=maxDescription;
    fieldSumLength=maxSum;
}

std::string Report_Save::row(const int row)const{
    char separatorFields=' ';
    int numberSeparatorFields=1;
    Record record=pData->getRecord(row);
    Record_String recordString(record);
    std::string result;
    result+=recordString.getDate()+separatorFields;
    std::string separatorType(fieldTypeLength-stringLength(recordString.getType())+numberSeparatorFields,separatorFields);
    std::string separatorCategory(fieldCategoryLength-stringLength(recordString.getCategory())+numberSeparatorFields,separatorFields);
    std::string separatorDescription (fieldDescriptionLength-stringLength(recordString.getDescription())+numberSeparatorFields,separatorFields);
    std::string separatorSum(fieldSumLength-stringLength(recordString.getSum())+numberSeparatorFields,separatorFields);
    result+=recordString.getType()+separatorType+
            recordString.getCategory()+separatorCategory+
            recordString.getDescription()+separatorDescription+
            recordString.getSum()+separatorSum+
            recordString.getCurrency()+"\n";
    return result;
}
