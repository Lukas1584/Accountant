#include "Report.h"

Report::Report(std::shared_ptr<Data>& data): QObject(),pData(data){}

std::vector<std::string> Report::getRow(const int row) const{
    int count=0;
    for(unsigned int i=0;i<filter.size();i++){
        if(filter[i]){
            if(count==row){
                std::vector<std::string> row;
                for(int column=0;column<pData->columns();column++)
                    row.push_back(pData->at(column,i));
                return row;
            }
            count++;
        }
    }
    std::vector<std::string> empty;
    return empty;
}

int Report::rowCount(){
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
    for(auto i:filter)
        if(i)
            size++;
}

void Report::filterDB(const std::string& dateFrom,
              const std::string& dateTo,
              const int type,
              const std::vector<std::string>& category,
              const std::vector<std::string>& description,
              const float& sumFrom,
              const float& sumTo,
              const std::vector<bool>& currency){
    for(int i=0;i<pData->rows();i++){
        if(dateInRange(pData->at(0,i),dateFrom,dateTo) &&
                typeInRange(pData->at(1,i),type) &&
                categoryInRange(pData->at(2,i),category) &&
                descriptionInRange(pData->at(3,i),description) &&
                sumInRange(pData->at(4,i),sumFrom,sumTo) &&
                currencyInRange(pData->at(5,i),currency) )
            filter[i]=true;
        else filter[i]=false;
    }
    sizeReport();
}

bool Report::typeInRange(const std::string& type,const int typeFilter){
    switch (typeFilter) {
    case (00):
        return false;
    case (01):
        if(type=="Убыток")
            return true;
        else
            return false;
    case (10):
        if(type=="Прибыль")
            return true;
        else
            return false;
    case (11):
        return true;
    default:
        return false;
    }
}

bool Report::currencyInRange(const std::string& currency,const std::vector<bool>& currencyFilter){
    if(currencyFilter[0] && currency=="USD")
        return true;
    if(currencyFilter[1] && currency=="BYR")
        return true;
    if(currencyFilter[2] && currency=="RUB")
        return true;
    if(currencyFilter[3] && currency=="EUR")
        return true;
    return false;
}

bool Report::categoryInRange(const std::string& category,const std::vector<std::string>& categoryFilter){
    for(auto i:categoryFilter)
        if(category==i)
            return true;
    return false;
}

bool Report::descriptionInRange(const std::string& description,const std::vector<std::string>& descriptionFilter){
    for(auto i:descriptionFilter)
        if(description==i)
            return true;
    return false;
}

bool Report::sumInRange(const std::string& sum,const float& sumFrom,const float& sumTo){
    std::stringstream ss;
    ss<<sum;
    float value;
    ss>>value;
    if(sumFrom<=value && value<=sumTo)
        return true;
    return false;
}

bool Report::dateInRange(const std::string& date,const std::string& dateFrom,const std::string& dateTo){
    if(dateFrom<=date && date<=dateTo)
        return true;
    return false;
}

std::list<std::string> Report::getCategories(const bool profit,const bool loss){
    std::list<std::string> categories;
    if(profit)
        categories=pData->getCategories("Прибыль");
    if(loss){
        std::list<std::string> temp;
        temp=pData->getCategories("Убыток");
        for(auto i:temp){
            bool isUnique=true;
            for(auto j:categories){
                if(i==j)
                    isUnique=false;
            }
            if(isUnique)
                categories.push_back(i);
        }
    }
    categories.sort();
    return categories;
}

std::list<std::string> Report::getDescriptions(const std::vector <std::string>& categories){
    std::list<std::string> description;
    for(auto i:categories){
        std::list<std::string> list;
        list=pData->getDescriprions(i);
        for(auto j:list){
            bool isUnique=true;
            for(auto k:description){
                if(k==j)
                    isUnique=false;
            }
            if(isUnique)
                description.push_back(j);
        }
    }
    description.sort();
    return description;
}

std::pair<std::string,std::string> Report::dateMinMax(){
    return {pData->at(0,0),pData->at(0,static_cast<int>(filter.size()-1))};
}

std::pair<std::string,std::string> Report::sumMinMax(){
    float max;
    float min;
    for (unsigned int i=0;i<filter.size();i++){
        std::string str=pData->at(4,i);
        std::stringstream ss;
        ss<<str;
        float tmp;
        ss>>tmp;
        if(i==0){
            max=tmp;
            min=tmp;
        }
        if(max<tmp)
            max=tmp;
        if (min>tmp)
            min=tmp;
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
