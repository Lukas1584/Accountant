#pragma once
#include "SRC/BusinessLogic/AbstractBusinessLogic.h"
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/DataOperations.h"
#include "SRC/BusinessLogic/BalanceCalculator.h"
#include "SRC/BusinessLogic/RecordsOperations.h"
#include "SRC/BusinessLogic/Report.h"
#include "SRC/BusinessLogic/ReportSaveTxt.h"
#include "SRC/BusinessLogic/UserFileOperations.h"
#include "SRC/BusinessLogic/ReportSaveTxt.h"
#include "SRC/BusinessLogic/ReportSavePdf.h"

class BusinessLogic:public AbstractBusinessLogic{
public:
    BusinessLogic(std::shared_ptr<AbstractData> data,std::shared_ptr<AbstractDataFileOperations> operations);

    int rowsCount()const override;
    int columnsCount()const override;
    void setData(const int, const RecordString&)override;
    RecordString getData(const int)const override;
    void removeRow(const int)override;
    void sortData()override;
    std::list<std::string> getAllCurrencies()const override;
    std::list<std::string> getAllTypes()const override;

    std::list<std::string> getDataCategories(const std::string&)const override;
    std::list<std::string> getDataDescriptions(const std::string&)const override;
    std::list<std::string> getCurrencies()const override;

    int rowsCountReport()const override;
    RecordString getReport(const int)const override;
    void filter(const std::string &dateFrom,
                const std::string &dateTo,
                const std::pair<bool, bool> &type,
                const std::vector<std::string> &category,
                const std::vector<std::string> &description,
                const double &sumFrom, const double &sumTo,
                const std::vector<std::string> &currency)override;
    std::list<std::string> getReportCategories(const bool profit,const bool loss)const override;
    std::list<std::string> getReportDescriptions(const std::vector<std::string>& categories)const override;
    std::pair<std::string,std::string> dateMinMax()const override;
    std::pair<double, double> sumMinMax()const override;
    void saveReportTxt(const std::string&, const std::string &currentDate)const override;
    void saveReportPDF(const std::string&, const std::string &currentDate)const override;
    void updateReport()override;

    std::string getBalance(const std::string&)const override;

    std::list<std::string> getUsersNames()const override;
    bool isUserCreated(const std::string& login, const std::string& password)override;
    bool loadData(const std::string& login, const std::string& password)override;
    void saveData()const override;
    void clearData()override;
    bool deleteUser(const std::string& login,const std::string& password)override;
    bool changePassword(const std::string& login,const std::string& oldPassword,const std::string& newPassword)override;

private:
    std::shared_ptr<AbstractData> pData;
    std::shared_ptr<AbstractDataFileOperations> pDataOperations;

    std::unique_ptr<BalanceCalculator> pCalculator;
    std::shared_ptr<RecordsOperations> pOperations;
    std::shared_ptr<Report> pReport;
    std::unique_ptr<UserFileOperations> pUserFileOperations;

    std::unique_ptr<ReportSaveTxt> pReportSaveTxt;
    std::unique_ptr<ReportSavePdf> pReportSavePdf;
};
