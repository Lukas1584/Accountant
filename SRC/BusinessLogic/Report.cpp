#include "Report.h"
constexpr char LOSS[]="Убыток";
constexpr char PROFIT[]="Прибыль";

Report::Report(std::shared_ptr<AbstractData>& data):pData(data){}

Record_String Report::getRow(const int row) const{
    int count=0;
    for(unsigned int i=0;i<filter.size();i++){
        if(filter[i]){
            if(count==row){
                Record_String rec(pData->getRecord(i));
                return rec;
            }
            count++;
        }
    }
    return {"","","","",0,""};
}

int Report::rowsCount() const{
    return size;
}

void Report::update(){
    size=pData->rows();
    filter.resize(size);
    std::fill(filter.begin(),filter.end(),true);
}

void Report::sizeReport(){
    size=0;
    for(const auto& i:filter)
        if(i)
            size++;
}

void Report::filterDB(const std::string& dateFrom,
                      const std::string& dateTo,
                      const std::pair<bool,bool>& type,
                      const std::vector<std::string>& category,
                      const std::vector<std::string>& description,
                      const double& sumFrom,
                      const double& sumTo,
                      const std::vector<std::string>& currency){
    for(int i=0;i<pData->rows();i++){
        Record_String rec=pData->getRecord(i);
        if(dateInRange(rec.getDate(),dateFrom,dateTo) &&
                typeInRange(rec.getType(),type) &&
                valueInRange(rec.getCategory(),category) &&
                valueInRange(rec.getDescription(),description) &&
                sumInRange(rec.getSum(),sumFrom,sumTo) &&
                valueInRange(rec.getCurrency(),currency) )
            filter[i]=true;
        else filter[i]=false;
    }
    sizeReport();
}

bool Report::typeInRange(const std::string& type,const std::pair<bool,bool> typeFilter) const{
    if(type==PROFIT && typeFilter.first)
        return true;
    if(type==LOSS && typeFilter.second)
        return true;
    return false;
}

bool Report::valueInRange(const std::string& value,const std::vector<std::string>& vector) const{
    for(const auto& i:vector)
        if(value==i)
            return true;
    return false;
}

bool Report::sumInRange(const double& sum,const double& sumFrom,const double& sumTo) const{
    if(sumFrom<=sum && sum<=sumTo)
        return true;
    return false;
}

bool Report::dateInRange(const std::string& date,const std::string& dateFrom,const std::string& dateTo) const{
    if(dateFrom<=date && date<=dateTo)
        return true;
    return false;
}

std::list<std::string> Report::getCategories(const bool profit,const bool loss) const{
    std::list<std::string> categories;
    for(int i=0;i<static_cast<int>(filter.size());i++){
        Record_String rec=pData->getRecord(i);
        if((profit && rec.getType()==PROFIT) || (loss && rec.getType()==LOSS)){
            std::string category=rec.getCategory();
            bool isUnique=true;
            for(const auto& j:categories){
                if(j==category)
                    isUnique=false;
            }
            if(isUnique)
                categories.push_back(category);
        }
    }
    categories.sort();
    return categories;
}

std::list<std::string> Report::getDescriptions(const std::vector <std::string>& categories) const{
    std::list<std::string> descriptions;
    for(int i=0;i<static_cast<int>(filter.size());i++){
        Record_String rec=pData->getRecord(i);
        for(const auto& j:categories){
            if(j==rec.getCategory()){
                std::string description=rec.getDescription();
                bool isUnique=true;
                for(const auto& j:descriptions){
                    if(j==description)
                        isUnique=false;
                }
                if(isUnique)
                    descriptions.push_back(description);
            }
        }
    }
    descriptions.sort();
    return descriptions;
}

std::pair<std::string,std::string> Report::dateMinMax() const{
    Record_String recMin=pData->getRecord(0);
    Record_String recMax=pData->getRecord(static_cast<int>(filter.size())-1);
    return {recMin.getDate(),recMax.getDate()};
}

std::pair<double, double> Report::sumMinMax() const{
    double max;
    double min;
    for(int i=0;i<static_cast<int>(filter.size());++i){
        Record_String rec=pData->getRecord(i);
        double sum=rec.getSum();
        if(i==0){
            max=sum;
            min=sum;
        }
        if(max<sum)
            max=sum;
        if (min>sum)
            min=sum;
    }
    return {min,max};
}

void Report::saveTxt(const std::string& fileName){
    Report_Save txt(pData,filter);
    txt.saveTxt(fileName);
}
