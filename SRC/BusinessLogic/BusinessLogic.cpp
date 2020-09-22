#include "BusinessLogic.h"

BusinessLogic::BusinessLogic(std::shared_ptr<AbstractData> data, std::shared_ptr<AbstractDataFileOperations> operations):
    pData(data),pDataOperations(operations){
    pOperations=std::make_shared<Records_Operations>(data);
    pCalculator=std::make_unique<Balance_Calculator>(data,pOperations);
    pReport=std::make_unique<Report>(data);
    pUserFileOperations=std::make_unique<User_File_Operations>(data,pDataOperations);
}

int BusinessLogic::rowsCount(){
    return pData->rows();
}
int BusinessLogic::columnsCount(){
    return pData->columns();
}
void BusinessLogic::setData(const int row, const Record_String& record){
    pData->setRecord(row,record);
}
Record_String BusinessLogic::getData(const int row){
    return pData->getRecord(row);
}
void BusinessLogic::removeRow(const int row){
    pData->remove(row);
}
void BusinessLogic::sortData(){
    pData->sort();
}
std::list<std::string> BusinessLogic::getDataCategories(const std::string& type){
    return pOperations->getCategories(type);
}
std::list<std::string> BusinessLogic::getDataDescriptions(const std::string& category){
    return pOperations->getDescriptions(category);
}

int BusinessLogic::rowsCountReport(){
    return pReport->rowsCount();
}
Record_String BusinessLogic::getReport(const int row){
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

std::list<std::string> BusinessLogic::getReportCategories(const bool profit, const bool loss){
    return pReport->getCategories(profit,loss);
}

std::list<std::string> BusinessLogic::getReportDescriptions(const std::vector<std::string> &categories){
    return pReport->getDescriptions(categories);
}

std::pair<std::string,std::string> BusinessLogic::dateMinMax(){
    return pReport->dateMinMax();
}

std::pair<double,double> BusinessLogic::sumMinMax(){
    return pReport->sumMinMax();
}

void BusinessLogic::saveReportTxt(const std::string& fileName){
    pReport->saveTxt(fileName);
}

std::string BusinessLogic::getBalance(const std::string& currentDate){
    return pCalculator->getBalance(currentDate);
}

std::list<std::string> BusinessLogic::getUsersNames(){
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

void BusinessLogic::saveData(){
    pUserFileOperations->saveData();
}

std::list<std::string> BusinessLogic::getCurrencies(){
    return pOperations->getCurrencies();
}

std::list<std::string> BusinessLogic::getAllCurrencies(){
    return pData->getAllCurrencies();
}
std::list<std::string> BusinessLogic::getAllTypes(){
    return pData->getAllTypes();
}

void BusinessLogic::updateReport(){
    pReport->update();
}
