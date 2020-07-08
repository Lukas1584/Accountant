#include "Report.h"

Report::Report(std::shared_ptr<Data>& data): QObject(),pData(data){}

std::vector<std::string> Report::getRow(const int row) const{
    int count=0;
    for(unsigned int i=0;i<filter.size();i++){
        if(filter[i]){
            if(count==row){
                std::vector<std::string> row;
                for(int column=0;column<pData->columns();column++)
                    row.push_back(pData->at(i,column));
                return row;
            }
            count++;
        }
    }
    std::vector<std::string> empty;
    return empty;
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
        if(dateInRange(pData->at(i,0),dateFrom,dateTo) &&
                typeInRange(pData->at(i,1),type) &&
                categoryInRange(pData->at(i,2),category) &&
                descriptionInRange(pData->at(i,3),description) &&
                sumInRange(pData->at(i,4),sumFrom,sumTo) &&
                currencyInRange(pData->at(i,5),currency) )
            filter[i]=true;
        else filter[i]=false;
    }
    sizeReport();
}

bool Report::typeInRange(const std::string& type,const int typeFilter) const{
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

bool Report::currencyInRange(const std::string& currency,const std::vector<bool>& currencyFilter) const{
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

bool Report::categoryInRange(const std::string& category,const std::vector<std::string>& categoryFilter) const{
    for(auto i:categoryFilter)
        if(category==i)
            return true;
    return false;
}

bool Report::descriptionInRange(const std::string& description,const std::vector<std::string>& descriptionFilter) const{
    for(auto i:descriptionFilter)
        if(description==i)
            return true;
    return false;
}

bool Report::sumInRange(const std::string& sum,const float& sumFrom,const float& sumTo) const{
    std::stringstream ss;
    ss<<sum;
    float value;
    ss>>value;
    if(sumFrom<=value && value<=sumTo)
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
    int typeColumn=1;
    int categoryColumn=2;
    for(int i=0;i<static_cast<int>(filter.size());i++){
        std::string type=pData->at(i,typeColumn);
        if((profit && type=="Прибыль") || (loss && type=="Убыток")){
            std::string category=pData->at(i,categoryColumn);
            bool isUnique=true;
            for(auto j:categories){
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
    int categoryColumn=2;
    int descriptionColumn=3;
    for(int i=0;i<static_cast<int>(filter.size());i++){
        std::string category=pData->at(i,categoryColumn);
        for(auto j:categories){
            if(j==category){
                std::string description=pData->at(i,descriptionColumn);
                bool isUnique=true;
                for(auto j:descriptions){
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
    int dateColumn=0;
    return {pData->at(0,dateColumn),pData->at(static_cast<int>(filter.size()-1),dateColumn)};
}

std::pair<std::string,std::string> Report::sumMinMax() const{
    float max;
    float min;
    for (unsigned int i=0;i<filter.size();i++){
        float sum=pData->getSum(i);
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
