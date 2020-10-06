#include "BusinessLogic.h"

BusinessLogic::BusinessLogic(std::shared_ptr<AbstractData> data, std::shared_ptr<AbstractDataFileOperations> operations):
    pData(data),pDataOperations(operations){
    pOperations=std::make_shared<RecordsOperations>(data);
    pCalculator=std::make_unique<BalanceCalculator>(data,pOperations);

    pUserFileOperations=std::make_unique<UserFileOperations>(data,pDataOperations);

    pReport=std::make_shared<Report>(data);
    pReportSaveTxt=std::make_unique<ReportSaveTxt>(pReport);
    pReportSavePdf=std::make_unique<ReportSavePdf>(pReport);
}

int BusinessLogic::rowsCount() const{
    return pData->rows();
}
int BusinessLogic::columnsCount() const{
    return pData->columns();
}
void BusinessLogic::setData(const int row, const RecordString& record){
    pData->setRecord(row,record);
}
RecordString BusinessLogic::getData(const int row) const{
    return pData->getRecord(row);
}
void BusinessLogic::removeRow(const int row){
    pData->remove(row);
}
void BusinessLogic::sortData(){
    pData->sort();
}
std::list<std::string> BusinessLogic::getDataCategories(const std::string& type) const{
    return pOperations->getCategories(type);
}
std::list<std::string> BusinessLogic::getDataDescriptions(const std::string& category) const{
    return pOperations->getDescriptions(category);
}

int BusinessLogic::rowsCountReport() const{
    return pReport->rowsCount();
}
RecordString BusinessLogic::getReport(const int row) const{
    return pReport->getRow(row);
}
void BusinessLogic::filter(const std::string& dateFrom,
                           const std::string& dateTo,
                           const std::pair<bool,bool>& type,
                           const std::vector<std::string>& category,
                           const std::vector<std::string>& description,
                           const double &sumFrom,
                           const double &sumTo,
                           const std::vector<std::string>& currency){
    pReport->filterDB(dateFrom,dateTo,type,category,description,sumFrom,sumTo,currency);
}

std::list<std::string> BusinessLogic::getReportCategories(const bool profit, const bool loss)const{
    return pReport->getCategories(profit,loss);
}

std::list<std::string> BusinessLogic::getReportDescriptions(const std::vector<std::string> &categories)const{
    return pReport->getDescriptions(categories);
}

std::pair<std::string,std::string> BusinessLogic::dateMinMax()const{
    return pReport->dateMinMax();
}

std::pair<double,double> BusinessLogic::sumMinMax()const{
    return pReport->sumMinMax();
}

void BusinessLogic::saveReportTxt(const std::string& fileName,const std::string& currentDate) const{
    pReportSaveTxt->saveTxt(fileName,pUserFileOperations->getUserName(),currentDate);
}

void BusinessLogic::saveReportPDF(const std::string& fileName,const std::string& currentDate) const{
    pReportSavePdf->savePDF(fileName,pUserFileOperations->getUserName(),currentDate);
}

std::string BusinessLogic::getBalance(const std::string& currentDate)const{
    return pCalculator->getBalance(currentDate);
}

std::list<std::string> BusinessLogic::getUsersNames() const{
    return pUserFileOperations->getUsersNames();
}
bool BusinessLogic::isUserCreated(const std::string &login, const std::string &password){
    return pUserFileOperations->isUserCreated(login,password);
}

bool BusinessLogic::loadData(const std::string& login, const std::string& password){
    return pUserFileOperations->loadData(login,password);
}
void BusinessLogic::clearData(){
    pUserFileOperations->clearData();
}
bool BusinessLogic::deleteUser(const std::string &login, const std::string &password){
    return pUserFileOperations->deleteUser(login,password);
}
bool BusinessLogic::changePassword(const std::string &login, const std::string &oldPassword, const std::string &newPassword){
    return pUserFileOperations->changedPassword(login,oldPassword,newPassword);
}

void BusinessLogic::saveData() const{
    pUserFileOperations->saveData();
}

std::list<std::string> BusinessLogic::getCurrencies() const{
    return pOperations->getCurrencies();
}

std::list<std::string> BusinessLogic::getAllCurrencies() const{
    return pData->getAllCurrencies();
}
std::list<std::string> BusinessLogic::getAllTypes() const{
    return pData->getAllTypes();
}

void BusinessLogic::updateReport(){
    pReport->update();
}

std::string BusinessLogic::getUserName()const{
    return pUserFileOperations->getUserName();
}
