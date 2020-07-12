#include "Report_Save.h"

Report_Save::Report_Save(const std::shared_ptr<Data>& data,const std::vector<bool>& fil)
    : pData(data),filter(fil){}

void Report_Save::saveTxt(const std::string& filename){
    std::ofstream file{filename};
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

std::string Report_Save::row(const int row)const{
    int fieldTypeLength=maxLength(1)+1;
    int fieldCategoryLength=maxLength(2)+1;
    int fieldDescriptionLength=maxLength(3)+1;
    int fieldSumLength=maxLength(4)+1;
    std::string result;
    result+=pData->at(row,0)+" ";
    std::string type=pData->at(row,1);
    std::string separatorType(fieldTypeLength-stringLength(type),' ');
    std::string category=pData->at(row,2);
    std::string separatorCategory(fieldCategoryLength-stringLength(category),' ');
    std::string description=pData->at(row,3);
    std::string separatorDescription (fieldDescriptionLength-stringLength(description),' ');
    std::string sum=pData->at(row,4);
    std::string separatorSum(fieldSumLength-stringLength(sum),' ');
    result+=type+separatorType+
            category+separatorCategory+
            description+separatorDescription+
            sum+separatorSum+
            pData->at(row,5)+"\n";
    return result;
}

int Report_Save::maxLength(const int column)const{
    int max=0;
    for(int i=0;i<static_cast<int>(filter.size());i++){
        if(filter[i]){
            int size=stringLength(pData->at(i,column));
            if(max<size)
                max=size;
        }
    }
    return max;
}




