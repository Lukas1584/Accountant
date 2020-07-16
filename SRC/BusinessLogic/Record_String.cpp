#include "Record_String.h"

Record_String::Record_String(const Record &row){
    date=row.getDate();
    Record::Type t=row.getType();
    if(t==Record::Type::LOSS)
        type="Убыток";
    if(t==Record::Type::PROFIT)
        type="Прибыль";
    category=row.getCategory();
    description=row.getDescription();
    std::stringstream ss;
    ss<<row.getSum();
    ss>>sum;
    Record::Currency c=row.getCurrency();
    if(c==Record::Currency::BYR)
        currency="BYR";
    if(c==Record::Currency::USD)
        currency="USD";
    if(c==Record::Currency::RUB)
        currency="RUB";
    if(c==Record::Currency::EUR)
        currency="EUR";
}

Record_String::Record_String(const std::string& dt,
                             const std::string& tp,
                             const std::string& ct,
                             const std::string& ds,
                             const std::string& sm,
                             const std::string& cr)
    :date(dt),type(tp),category(ct),description(ds),sum(sm),currency(cr){
}

Record Record_String::convertToRecord() const{
    Record record;
    record.setDate(date);
    if(type=="Прибыль")
        record.setType(Record::Type::PROFIT);
    if(type=="Убыток")
        record.setType(Record::Type::LOSS);
    record.setCategory(category);
    record.setDescription(description);
    std::stringstream ss;
    ss<<sum;
    float s;
    ss>>s;
    record.setSum(s);
    if(currency=="USD")
        record.setCurrency(Record::Currency::USD);
    if(currency=="BYR")
        record.setCurrency(Record::Currency::BYR);
    if(currency=="RUB")
        record.setCurrency(Record::Currency::RUB);
    if(currency=="EUR")
        record.setCurrency(Record::Currency::EUR);
    return record;
}

std::string Record_String::getSum()const{
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



