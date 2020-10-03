#pragma once
#include "SRC/DataBase/Data.h"
#include "SRC/BusinessLogic/RecordString.h"
#include <list>

class Report{
public:
    explicit Report(std::shared_ptr<AbstractData>& data);
    RecordString getRow(const int row) const;
    int rowsCount()const;
    std::list<std::string> getCategories(const bool profit,const bool loss)const;
    std::list<std::string> getDescriptions(const std::vector<std::string>& categories)const;
    void filterDB(const std::string& dateFrom,
                  const std::string& dateTo,
                  const std::pair<bool, bool>& type,
                  const std::vector<std::string>& category,
                  const std::vector<std::string>& description,
                  const double &sumFrom,
                  const double &sumTo,
                  const std::vector<std::string> &currency);
    std::pair<std::string,std::string> dateMinMax()const;
    std::pair<double, double> sumMinMax()const;

    void update();

    std::string getDateFrom()const;
    std::string getDateTo()const;
    std::pair<bool,bool> getType()const;
    std::vector<std::string> getCategory()const;
    std::vector<std::string> getDescription()const;
    double getSumFrom()const;
    double getSumTo()const;
    std::vector<std::string> getCurrency()const;

private:
    int size;
    std::shared_ptr<AbstractData> pData;
    std::vector<bool> filter;

    void sizeReport();
    bool dateInRange(const std::string& date,const std::string& dateFrom,const std::string& dateTo)const;
    bool typeInRange(const std::string& type, const std::pair<bool,bool> typeFilter)const;
    bool valueInRange(const std::string& category,const std::vector<std::string>& categoryFilter)const;
    bool sumInRange(const double &sum, const double &sumFrom, const double &sumTo)const;

    std::string dateFrom;
    std::string dateTo;
    std::pair<bool,bool> type;
    std::vector<std::string> category;
    std::vector<std::string> description;
    double sumFrom;
    double sumTo;
    std::vector<std::string> currency;
};


