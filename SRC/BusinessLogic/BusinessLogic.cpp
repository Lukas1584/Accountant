#include "BusinessLogic.h"

BusinessLogic::BusinessLogic(std::shared_ptr<AbstractData> data, std::shared_ptr<AbstractDataFileOperations> operations):
    pData(data),pDataOperations(operations){
    pOperations=std::make_shared<RecordsOperations>(data);
    pCalculator=std::make_unique<BalanceCalculator>(data,pOperations);

    pUserFileOperations=std::make_unique<UserFileOperations>();

    pReport=std::make_shared<Report>(data);
    pReportSaveTxt=std::make_unique<ReportSaveTxt>(pReport);
    //pReportSavePdf=std::make_unique<ReportSavePdf>(pReport);

    pGraphicBuilder=std::make_unique<GraphicBuilder>(pReport);
}

unsigned int BusinessLogic::rowsCount() const{
    return pData->rows();
}
unsigned int BusinessLogic::columnsCount() const{
    return pData->columns();
}
void BusinessLogic::setData(const unsigned int row, const RecordString& record){
    pData->setRecord(row,record);
}
RecordString BusinessLogic::getData(const unsigned int row) const{
    return pData->getRecord(row);
}
void BusinessLogic::removeRow(const unsigned int row){
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

unsigned int BusinessLogic::rowsCountReport() const{
    return pReport->rowsCount();
}
RecordString BusinessLogic::getReport(const unsigned int row) const{
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
    //pReportSavePdf->savePDF(fileName,pUserFileOperations->getUserName(),currentDate);
}

std::string BusinessLogic::getBalance(const std::string& currentDate)const{
    return pCalculator->getBalance(currentDate);
}

std::list<std::string> BusinessLogic::getUsersNames() const{
    return pUserFileOperations->getUsersNames();
}
bool BusinessLogic::isUserCreated(const std::string &login, const std::string &password){
    bool result=pUserFileOperations->isUserCreated(login,password);
    if(result) pDataOperations->saveToFile(pUserFileOperations->getUserName());
    return result;
}

bool BusinessLogic::loadData(const std::string& login, const std::string& password){
    bool result=pUserFileOperations->checkPassword({login,password});
    if(result) pDataOperations->loadFromFile(pUserFileOperations->getUserName());
    return result;
}
void BusinessLogic::clearData(){
    pData->clear();
}
bool BusinessLogic::deleteUser(const std::string &login, const std::string &password){
    bool result=pUserFileOperations->deleteUser(login,password);
    if(result) pDataOperations->deleteFile(pUserFileOperations->getUserName());
    return result;
}
bool BusinessLogic::changePassword(const std::string &login, const std::string &oldPassword, const std::string &newPassword){
    return pUserFileOperations->changedPassword(login,oldPassword,newPassword);
}

void BusinessLogic::saveData() const{
    pDataOperations->saveToFile(pUserFileOperations->getUserName());
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

std::pair<double,double> BusinessLogic::getMinMaxSum(){
    return pGraphicBuilder->getMinMaxSum();
}
std::vector<std::pair<std::string,double>> BusinessLogic::getPoints(){
    return pGraphicBuilder->getPoints();
}

void BusinessLogic::printReport(const std::string& currentDate){
    ReportPrint report(pReport);
    report.printReport(pUserFileOperations->getUserName(),currentDate);
}
