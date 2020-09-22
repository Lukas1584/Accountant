#pragma once
#include "SRC/BusinessLogic/AbstractBusinessLogic.h"
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/DataOperations.h"
#include "SRC/BusinessLogic/Balance_Calculator.h"
#include "SRC/BusinessLogic/Records_Operations.h"
#include "SRC/BusinessLogic/Report.h"
#include "SRC/BusinessLogic/Report_Save.h"
#include "SRC/BusinessLogic/User_File_Operations.h"

class BusinessLogic:public AbstractBusinessLogic{
public:
    BusinessLogic(std::shared_ptr<AbstractData> data,std::shared_ptr<AbstractDataFileOperations> operations);

    int rowsCount()override;
    int columnsCount()override;
    void setData(const int, const Record_String&)override;
    Record_String getData(const int)override;
    void removeRow(const int)override;
    void sortData()override;
    std::list<std::string> getAllCurrencies()override;
    std::list<std::string> getAllTypes()override;

    std::list<std::string> getDataCategories(const std::string&)override;
    std::list<std::string> getDataDescriptions(const std::string&)override;
    std::list<std::string> getCurrencies()override;

    int rowsCountReport()override;
    Record_String getReport(const int)override;
    void filter(const std::string &dateFrom,
                const std::string &dateTo,
                const std::pair<bool, bool> &type,
                const std::vector<std::string> &category,
                const std::vector<std::string> &description,
                const double &sumFrom, const double &sumTo,
                const std::vector<std::string> &currency)override;
    std::list<std::string> getReportCategories(const bool profit,const bool loss)override;
    std::list<std::string> getReportDescriptions(const std::vector<std::string>& categories)override;
    std::pair<std::string,std::string> dateMinMax()override;
    std::pair<double, double> sumMinMax()override;
    void saveReportTxt(const std::string&)override;
    void updateReport()override;

    std::string getBalance(const std::string&)override;

    std::list<std::string> getUsersNames()override;
    bool isUserCreated(const std::string& login, const std::string& password)override;
    bool loadData(const std::string& login, const std::string& password)override;
    void saveData()override;
    void clearData()override;
    bool deleteUser(const std::string& login,const std::string& password)override;
    bool changePassword(const std::string& login,const std::string& oldPassword,const std::string& newPassword)override;

private:
    std::shared_ptr<AbstractData> pData;
    std::shared_ptr<AbstractDataFileOperations> pDataOperations;

    std::unique_ptr<Balance_Calculator> pCalculator;
    std::shared_ptr<Records_Operations> pOperations;
    std::unique_ptr<Report> pReport;
    std::unique_ptr<User_File_Operations> pUserFileOperations;
};
