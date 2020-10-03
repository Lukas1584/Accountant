#pragma once
#include <string>

class RecordString{
public:
    RecordString(const std::string& dt,
                  const std::string& tp,
                  const std::string& ct,
                  const std::string& ds,
                  const double sm,
                  const std::string& cr);

    double getSum()const;
    std::string getDate()const;
    std::string getType()const;
    std::string getCategory()const;
    std::string getDescription()const;
    std::string getCurrency()const;

private:
    std::string date;
    std::string type;
    std::string category;
    std::string description;
    double sum;
    std::string currency;
};

