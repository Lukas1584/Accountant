#pragma once
#include <QObject>
#include <memory>
#include <vector>
#include "SRC/DataBase/Data.h"

class Report:public QObject
{
    Q_OBJECT
public:
    explicit Report(std::shared_ptr<Data>& data);
    std::vector<std::string> getRow(const int row) const;
    int rowCount();
    int columnCount()const;

    void setDateFrom(const std::string& date);
    void setDateTo(const std::string& date);
    std::list<std::string> getCategories(const bool profit,const bool loss);
    std::list<std::string> getDescriptions(const std::vector<std::string> &categories);
    void filterDB(const std::string& dateFrom,
                  const std::string& dateTo,
                  const int type,
                  const std::vector<std::string>& category,
                  const std::vector<std::string>& description,
                  const float& sumFrom,
                  const float& sumTo,
                  const std::vector<bool> &currency);
    std::pair<std::string,std::string> dateMinMax();
    std::pair<std::string,std::string> sumMinMax();

signals:

public slots:
    void update();

private:
    int size;
    std::shared_ptr<Data> pData;
    std::vector<bool> filter;

    void sizeReport();
    bool dateInRange(const std::string& date,const std::string& dateFrom,const std::string& dateTo);
    bool typeInRange(const std::string& type,const int typeFilter);
    bool categoryInRange(const std::string& category,const std::vector<std::string>& categoryFilter);
    bool descriptionInRange(const std::string& description,const std::vector<std::string>& descriptionFilter);
    bool sumInRange(const std::string& sum,const float& sumFrom,const float& sumTo);
    bool currencyInRange(const std::string& currency, const std::vector<bool>& currencyFilter);

};


