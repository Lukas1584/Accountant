#pragma once
#include <list>
#include <vector>
#include "SRC/BusinessLogic/Record_String.h"

class AbstractBusinessLogic{
public:
    virtual int rowsCount()=0;
    virtual int columnsCount()=0;
    virtual void setData(const int, const Record_String&)=0;
    virtual Record_String getData(const int)=0;
    virtual void removeRow(const int)=0;
    virtual void sortData()=0;
    virtual std::list<std::string> getAllCurrencies()=0;
    virtual std::list<std::string> getAllTypes()=0;

    virtual std::list<std::string> getDataCategories(const std::string&)=0;
    virtual std::list<std::string> getDataDescriptions(const std::string&)=0;
    virtual std::list<std::string> getCurrencies()=0;

    virtual int rowsCountReport()=0;
    virtual Record_String getReport(const int)=0;
    virtual void filter(const std::string& dateFrom,
                        const std::string& dateTo,
                        const std::pair<bool,bool>& type,
                        const std::vector<std::string>& category,
                        const std::vector<std::string>& description,
                        const double& sumFrom,
                        const double& sumTo,
                        const std::vector<std::string>& currency)=0;
    virtual std::list<std::string> getReportCategories(const bool,const bool)=0;
    virtual std::list<std::string> getReportDescriptions(const std::vector<std::string>&)=0;
    virtual std::pair<std::string,std::string> dateMinMax()=0;
    virtual std::pair<double, double> sumMinMax()=0;
    virtual void saveReportTxt(const std::string&)=0;
    virtual void updateReport()=0;

    virtual std::string getBalance(const std::string&)=0;

    virtual std::list<std::string> getUsersNames()=0;
    virtual bool isUserCreated(const std::string& login, const std::string& password)=0;
    virtual bool loadData(const std::string& login, const std::string& password)=0;
    virtual void saveData()=0;
    virtual void clearData()=0;
    virtual bool deleteUser(const std::string& login,const std::string& password)=0;
    virtual bool changePassword(const std::string& login,const std::string& oldPassword,const std::string& newPassword)=0;
};
