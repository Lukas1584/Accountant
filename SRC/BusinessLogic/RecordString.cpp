#include "RecordString.h"

RecordString::RecordString(const std::string& dt,
                             const std::string& tp,
                             const std::string& ct,
                             const std::string& ds,
                             const double sm,
                             const std::string& cr)
    :date(dt),type(tp),category(ct),description(ds),sum(sm),currency(cr){
}

double RecordString::getSum()const{
    return sum;
}

std::string RecordString::getDate()const{
    return date;
}

std::string RecordString::getType()const{
    return type;
}

std::string RecordString::getCategory()const{
    return category;
}
std::string RecordString::getDescription()const{
    return description;
}

std::string RecordString::getCurrency()const{
    return currency;
}



