#pragma once
#include "SRC/DataBase/Data.h"
#include "SRC/BusinessLogic/Report_Save.h"
#include "SRC/BusinessLogic/Record_String.h"
#include <list>

class Report{
public:
    explicit Report(std::shared_ptr<AbstractData>& data);
    Record_String getRow(const int row) const;
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
    void saveTxt(const std::string& fileName);

    void update();

private:
    int size;
    std::shared_ptr<AbstractData> pData;
    std::vector<bool> filter;

    void sizeReport();
    bool dateInRange(const std::string& date,const std::string& dateFrom,const std::string& dateTo)const;
    bool typeInRange(const std::string& type, const std::pair<bool,bool> typeFilter)const;
    bool valueInRange(const std::string& category,const std::vector<std::string>& categoryFilter)const;
    bool sumInRange(const double &sum, const double &sumFrom, const double &sumTo)const;
};


