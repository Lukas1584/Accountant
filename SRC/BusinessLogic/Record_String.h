#pragma once
#include "SRC/DataBase/Record.h"
#include <string>



class Record_String{
public:
    Record_String(const Record& row);
    Record_String(const std::string& dt,
                  const std::string& tp,
                  const std::string& ct,
                  const std::string& ds,
                  const std::string& sm,
                  const std::string& cr);

    Record convertToRecord()const;

    std::string getSum()const;
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
    std::string sum;
    std::string currency;
};

