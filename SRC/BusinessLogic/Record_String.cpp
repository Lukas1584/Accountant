#include "Record_String.h"

Record_String::Record_String(const std::string& dt,
                             const std::string& tp,
                             const std::string& ct,
                             const std::string& ds,
                             const double sm,
                             const std::string& cr)
    :date(dt),type(tp),category(ct),description(ds),sum(sm),currency(cr){
}

double Record_String::getSum()const{
    return sum;
}

std::string Record_String::getDate()const{
    return date;
}

std::string Record_String::getType()const{
    return type;
}

std::string Record_String::getCategory()const{
    return category;
}
std::string Record_String::getDescription()const{
    return description;
}

std::string Record_String::getCurrency()const{
    return currency;
}



