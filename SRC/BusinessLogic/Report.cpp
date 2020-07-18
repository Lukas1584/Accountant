#include "Report.h"

Report::Report(std::shared_ptr<Data>& data, QObject* pobj): QObject(pobj),pData(data){}

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
    return {"","","","","",""};
}

int Report::rowCount() const{
    return size;
}

int Report::columnCount() const{
    return pData->columns();
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
              const float& sumFrom,
              const float& sumTo,
              const std::vector<bool>& currency){
    for(int i=0;i<pData->rows();i++){
        Record rec=pData->getRecord(i);
        if(dateInRange(rec.getDate(),dateFrom,dateTo) &&
                typeInRange(rec.getType(),type) &&
                categoryInRange(rec.getCategory(),category) &&
                descriptionInRange(rec.getDescription(),description) &&
                sumInRange(rec.getSum(),sumFrom,sumTo) &&
                currencyInRange(rec.getCurrency(),currency) )
            filter[i]=true;
        else filter[i]=false;
    }
    sizeReport();
}

bool Report::typeInRange(const Record::Type type,const std::pair<bool,bool> typeFilter) const{
    if(type==Record::Type::PROFIT && typeFilter.first)
        return true;
    if(type==Record::Type::LOSS && typeFilter.second)
        return true;
    return false;
}

bool Report::currencyInRange(const Record::Currency currency,const std::vector<bool>& currencyFilter) const{
    if(currencyFilter[0] && currency==Record::Currency::USD)
        return true;
    if(currencyFilter[1] && currency==Record::Currency::BYR)
        return true;
    if(currencyFilter[2] && currency==Record::Currency::RUB)
        return true;
    if(currencyFilter[3] && currency==Record::Currency::EUR)
        return true;
    return false;
}

bool Report::categoryInRange(const std::string& category,const std::vector<std::string>& categoryFilter) const{
    for(const auto& i:categoryFilter)
        if(category==i)
            return true;
    return false;
}

bool Report::descriptionInRange(const std::string& description,const std::vector<std::string>& descriptionFilter) const{
    for(const auto& i:descriptionFilter)
        if(description==i)
            return true;
    return false;
}

bool Report::sumInRange(const float& sum,const float& sumFrom,const float& sumTo) const{
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
        Record rec=pData->getRecord(i);
        if((profit && rec.getType()==Record::Type::PROFIT) || (loss && rec.getType()==Record::Type::LOSS)){
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
        Record rec=pData->getRecord(i);
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
    Record recMin=pData->getRecord(0);
    Record recMax=pData->getRecord(static_cast<int>(filter.size())-1);
    return {recMin.getDate(),recMax.getDate()};
}

std::pair<std::string,std::string> Report::sumMinMax() const{
    float max;
    float min;
    for (unsigned int i=0;i<filter.size();i++){
        Record rec=pData->getRecord(i);
        float sum=rec.getSum();
        if(i==0){
            max=sum;
            min=sum;
        }
        if(max<sum)
            max=sum;
        if (min>sum)
            min=sum;
    }
    std::stringstream ss;
    ss<<min;
    std::string strMin;
    ss>>strMin;
    ss.clear();
    ss<<max;
    std::string strMax;
    ss>>strMax;
    return {strMin,strMax};
}

void Report::saveTxt(const std::string& fieName){
    Report_Save txt(pData,filter);
    txt.saveTxt(fieName);
}
