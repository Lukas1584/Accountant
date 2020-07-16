#pragma once
#include <QObject>
#include "SRC/DataBase/Data.h"
#include "SRC/BusinessLogic/Report_Save.h"
#include "SRC/BusinessLogic/Record_String.h"

class Report:public QObject
{
    Q_OBJECT
public:
    explicit Report(std::shared_ptr<Data>& data,QObject* pobj=nullptr);
    Record_String getRow(const int row) const;
    int rowCount()const;
    int columnCount()const;
    std::list<std::string> getCategories(const bool profit,const bool loss)const;
    std::list<std::string> getDescriptions(const std::vector<std::string>& categories)const;
    void filterDB(const std::string& dateFrom,
                  const std::string& dateTo,
                  const int type,
                  const std::vector<std::string>& category,
                  const std::vector<std::string>& description,
                  const float& sumFrom,
                  const float& sumTo,
                  const std::vector<bool>& currency);
    std::pair<std::string,std::string> dateMinMax()const;
    std::pair<std::string,std::string> sumMinMax()const;
    void saveTxt(const std::string& fieName);

signals:

private slots:
    void update();

private:
    int size;
    std::shared_ptr<Data> pData;
    std::vector<bool> filter;

    void sizeReport();
    bool dateInRange(const std::string& date,const std::string& dateFrom,const std::string& dateTo)const;
    bool typeInRange(const Record::Type type,const int typeFilter)const;
    bool categoryInRange(const std::string& category,const std::vector<std::string>& categoryFilter)const;
    bool descriptionInRange(const std::string& description,const std::vector<std::string>& descriptionFilter)const;
    bool sumInRange(const float& sum,const float& sumFrom,const float& sumTo)const;
    bool currencyInRange(const Record::Currency currency, const std::vector<bool>& currencyFilter)const;
};


