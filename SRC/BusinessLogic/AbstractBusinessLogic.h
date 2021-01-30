#pragma once
#include <list>
#include <vector>
#include <string>
#include "SRC/BusinessLogic/RecordString.h"

class AbstractBusinessLogic{
public:
    //Data Base
    virtual unsigned int rowsCount()const=0;
    virtual unsigned int columnsCount()const=0;
    virtual void setData(const unsigned int, const RecordString&)=0;
    virtual RecordString getData(const unsigned int)const=0;
    virtual void removeRow(const unsigned int)=0;
    virtual void sortData()=0;
    virtual std::list<std::string> getAllCurrencies()const=0;
    virtual std::list<std::string> getAllTypes()const=0;

    virtual std::list<std::string> getDataCategories(const std::string&)const=0;
    virtual std::list<std::string> getDataDescriptions(const std::string&)const=0;
    virtual std::list<std::string> getCurrencies()const=0;
    //Report
    virtual unsigned int rowsCountReport()const=0;
    virtual RecordString getReport(const unsigned int)const=0;
    virtual void filter(const std::string& dateFrom,
                        const std::string& dateTo,
                        const std::pair<bool,bool>& type,
                        const std::vector<std::string>& category,
                        const std::vector<std::string>& description,
                        const double& sumFrom,
                        const double& sumTo,
                        const std::vector<std::string>& currency)=0;
    virtual std::list<std::string> getReportCategories(const bool,const bool)const=0;
    virtual std::list<std::string> getReportDescriptions(const std::vector<std::string>&)const=0;
    virtual std::pair<std::string,std::string> dateMinMax()const=0;
    virtual std::pair<double, double> sumMinMax()const=0;
    virtual void saveReportTxt(const std::string&,const std::string&)const=0;
    virtual void saveReportPDF(const std::string&, const std::string &currentDate)const=0;
    virtual void updateReport()=0;
    //Balance
    virtual std::string getBalance(const std::string&)const=0;
    //User operations
    virtual std::list<std::string> getUsersNames()const=0;
    virtual bool isUserCreated(const std::string& login, const std::string& password)=0;
    virtual bool loadData(const std::string& login, const std::string& password)=0;
    virtual void saveData()const=0;
    virtual void clearData()=0;
    virtual bool deleteUser(const std::string& login,const std::string& password)=0;
    virtual bool changePassword(const std::string& login,const std::string& oldPassword,const std::string& newPassword)=0;
    virtual std::string getUserName()const=0;
    //Graphic
    virtual std::pair<double,double> getMinMaxSum()=0;
    virtual std::vector<std::pair<std::string,double>> getPoints()=0;
    virtual void printReport(const std::string& currentDate)=0;
};
