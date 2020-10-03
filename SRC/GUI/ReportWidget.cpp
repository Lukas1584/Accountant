#include "ReportWidget.h"

ReportWidget::ReportWidget(std::shared_ptr<AbstractBusinessLogic> logic, QWidget *parent) : QWidget(parent),pLogic(logic){
    pTable=new QTableWidget(this);
    pTable->installEventFilter(this);

    pBtnSaveTxt=new QPushButton(tr("Сохранить TXT"));
    pBtnSavePDF=new QPushButton(tr("Сохранить в PDF"));
    pBtnPrint=new QPushButton(tr("Печать"));
    pBtnChart=new QPushButton(tr("График"));
    pBtnReset=new QPushButton(tr("Сбросить фильтр"));

    QVBoxLayout* pVbxButtons=new QVBoxLayout;
    pVbxButtons->addWidget(pBtnSaveTxt);
    pVbxButtons->addWidget(pBtnSavePDF);
    pVbxButtons->addWidget(pBtnPrint);
    pVbxButtons->addWidget(pBtnChart);
    pVbxButtons->addStretch(1);

    QLabel* pLblDateFrom=new QLabel(tr("От:"));
    pTimeEditFrom=new QDateEdit();
    QLabel* pLblDateTo=new QLabel(tr("До:"));
    pTimeEditTo=new QDateEdit();
    QVBoxLayout* pVbxDate=new QVBoxLayout;
    pVbxDate->addWidget(pLblDateFrom);
    pVbxDate->addWidget(pTimeEditFrom);
    pVbxDate->addWidget(pLblDateTo);
    pVbxDate->addWidget(pTimeEditTo);
    pVbxDate->addStretch(1);

    QLabel* pLblType=new QLabel(tr("Тип:"));
    pChbxTypeProfit=new QCheckBox(tr("Прибыль"));
    pChbxTypeLoss=new QCheckBox(tr("Убыток"));
    QVBoxLayout* pVbxType=new QVBoxLayout;
    pVbxType->addWidget(pLblType);
    pVbxType->addWidget(pChbxTypeProfit);
    pVbxType->addWidget(pChbxTypeLoss);
    pVbxType->addStretch(1);

    QLabel* pLblCategory=new QLabel(tr("Категория:"));
    pCbxCategory=new QComboBox;
    pModelCategory = new QStandardItemModel(0, 1);
    pCbxCategory->setModel(pModelCategory);
    QVBoxLayout* pVbxCategory=new QVBoxLayout;
    pVbxCategory->addWidget(pLblCategory);
    pVbxCategory->addWidget(pCbxCategory);
    pVbxCategory->addStretch(1);

    QLabel* pLblDescription=new QLabel(tr("Описание:"));
    pCbxDescription=new QComboBox;
    pModelDescription = new QStandardItemModel(0, 1);
    pCbxDescription->setModel(pModelDescription);
    QVBoxLayout* pVbxDescription=new QVBoxLayout;
    pVbxDescription->addWidget(pLblDescription);
    pVbxDescription->addWidget(pCbxDescription);
    pVbxDescription->addStretch(1);

    QLabel* pLblSumFrom=new QLabel(tr("Сумма от:"));
    pLineEditSumFrom=new QLineEdit;
    QLabel* pLblSumTo=new QLabel(tr("Сумма до:"));
    pLineEditSumTo=new QLineEdit;
    QVBoxLayout* pVbxSum=new QVBoxLayout;
    pVbxSum->addWidget(pLblSumFrom);
    pVbxSum->addWidget(pLineEditSumFrom);
    pVbxSum->addWidget(pLblSumTo);
    pVbxSum->addWidget(pLineEditSumTo);
    pVbxSum->addStretch(1);

    QLabel* pLblCurrency=new QLabel(tr("Валюта:"));
    pCbxCurrency=new QComboBox;
    pModelCurrency = new QStandardItemModel(0, 1);
    pCbxCurrency->setModel(pModelCurrency);
    QVBoxLayout* pVbxCurrency=new QVBoxLayout;
    pVbxCurrency->addWidget(pLblCurrency);
    pVbxCurrency->addWidget(pCbxCurrency);
    pVbxCurrency->addStretch(1);

    QHBoxLayout* pHbxFilter=new QHBoxLayout;
    pHbxFilter->addLayout(pVbxDate,2);
    pHbxFilter->addLayout(pVbxType,1);
    pHbxFilter->addLayout(pVbxCategory,4);
    pHbxFilter->addLayout(pVbxDescription,4);
    pHbxFilter->addLayout(pVbxSum,2);
    pHbxFilter->addLayout(pVbxCurrency,1);

    QHBoxLayout* pHbxButtonsFilter=new QHBoxLayout;
    pHbxButtonsFilter->addWidget(pBtnReset);
    pHbxButtonsFilter->addWidget(pBtnChart);

    QVBoxLayout* pVbxFilter=new QVBoxLayout;
    pVbxFilter->addLayout(pHbxFilter);
    pVbxFilter->addLayout(pHbxButtonsFilter);

    QHBoxLayout* pHbxButtonsAndFilter=new QHBoxLayout;
    pHbxButtonsAndFilter->addLayout(pVbxFilter);
    pHbxButtonsAndFilter->addLayout(pVbxButtons);

    QVBoxLayout* pVbxMain=new QVBoxLayout;
    pVbxMain->addLayout(pHbxButtonsAndFilter,1);
    pVbxMain->addWidget(pTable,6);
    setLayout(pVbxMain);

    QObject::connect(pChbxTypeProfit,SIGNAL(clicked()),SLOT(fillComboBoxCategory()));
    QObject::connect(pChbxTypeLoss,SIGNAL(clicked()),SLOT(fillComboBoxCategory()));

    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(categoryChecked(QStandardItem*)));
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(fillComboBoxDescription()));

    QObject::connect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),SLOT(descriptionChecked(QStandardItem*)));
    QObject::connect(pModelCurrency,SIGNAL(itemChanged(QStandardItem*)),SLOT(currencyChecked(QStandardItem*)));


    QObject::connect(pBtnReset,SIGNAL(clicked()),SLOT(resetFilter()));
    QObject::connect(pBtnSaveTxt,SIGNAL(clicked()),SLOT(saveTxt()));
    QObject::connect(pBtnSavePDF,SIGNAL(clicked()),SLOT(savePDF()));
    QObject::connect(pBtnPrint,SIGNAL(clicked()),SLOT(print()));


    QObject::connect(pTimeEditFrom,SIGNAL(dateChanged(const QDate&)),SLOT(filter()));
    QObject::connect(pTimeEditTo,SIGNAL(dateChanged(const QDate&)),SLOT(filter()));
    QObject::connect(pChbxTypeProfit,SIGNAL(clicked()),SLOT(filter()));
    QObject::connect(pChbxTypeLoss,SIGNAL(clicked()),SLOT(filter()));
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(filter()));
    QObject::connect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),SLOT(filter()));
    QObject::connect(pModelCurrency,SIGNAL(itemChanged(QStandardItem*)),SLOT(filter()));
    QObject::connect(pLineEditSumFrom,SIGNAL(textChanged(const QString&)),SLOT(filter()));
    QObject::connect(pLineEditSumTo,SIGNAL(textChanged(const QString&)),SLOT(filter()));
}

void ReportWidget::updateTable(){
    int rows=pLogic->rowsCountReport();
    int columns=pLogic->columnsCount();
    pTable->setRowCount(rows);
    pTable->setColumnCount(columns);
    for(int row = 0;row<rows;row++){
        RecordString rec=pLogic->getReport(row);
        QTableWidgetItem* item0 = new QTableWidgetItem(rec.getDate().c_str());
        pTable->setItem(row,0,item0);
        QTableWidgetItem* item1 = new QTableWidgetItem(rec.getType().c_str());
        pTable->setItem(row,1,item1);
        QTableWidgetItem* item2 = new QTableWidgetItem(rec.getCategory().c_str());
        pTable->setItem(row,2,item2);
        QTableWidgetItem* item3 = new QTableWidgetItem(rec.getDescription().c_str());
        pTable->setItem(row,3,item3);
        QTableWidgetItem* item4 = new QTableWidgetItem(QString::number(rec.getSum()));
        pTable->setItem(row,4,item4);
        QTableWidgetItem* item5 = new QTableWidgetItem(rec.getCurrency().c_str());
        pTable->setItem(row,5,item5);
    }
    setTableHeader();
    setTableDimensions();
}

void ReportWidget::setTableHeader(){
    std::vector<std::string> header{"Дата","Тип","Категория","Описание","Сумма","Валюта"};
    for(int i=0;i< pLogic->columnsCount();i++){
        QTableWidgetItem* item=new QTableWidgetItem(header[i].c_str());
        pTable->setHorizontalHeaderItem(i,item);
    }
    pTable->verticalHeader()->hide();
}

void ReportWidget::setTableDimensions(){
    pTable->setColumnWidth(0, pTable->width() * 0.1);
    pTable->setColumnWidth(1, pTable->width() * 0.1);
    pTable->setColumnWidth(2, pTable->width() * 0.28);
    pTable->setColumnWidth(3, pTable->width() * 0.3);
    pTable->setColumnWidth(4, pTable->width() * 0.1);
    pTable->setColumnWidth(5, pTable->width() * 0.1);
}

bool ReportWidget::eventFilter(QObject* , QEvent *pEvent){
    if(pEvent->type() == QEvent::Resize )
        setTableDimensions();
    return false;
}

void ReportWidget::filter(){
    pLogic->filter(pTimeEditFrom->date().toString("yyyy-MM-dd").toStdString(),
                      pTimeEditTo->date().toString("yyyy-MM-dd").toStdString(),
                      typeToReport(),
                      getComboBoxCheckedList(pCbxCategory),
                      getComboBoxCheckedList(pCbxDescription),
                      pLineEditSumFrom->text().toFloat(),
                      pLineEditSumTo->text().toDouble(),
                      getComboBoxCheckedList(pCbxCurrency));
    updateTable();
}

std::pair<bool,bool> ReportWidget::typeToReport() const{
    std::pair<bool,bool> type {false,false};
    if (pChbxTypeProfit->isChecked())
        type.first=true;
    if(pChbxTypeLoss->isChecked())
        type.second=true;
    return type;
}

void ReportWidget::fillFields(){
    pChbxTypeProfit->setChecked(true);
    pChbxTypeLoss->setChecked(true);
    fillComboBoxCategory();
    fillComboBoxDescription();
    fillDate();
    fillSum();
    fillComboBoxCurrency();
}

void ReportWidget::fillComboBoxCurrency(){
    std::list<std::string> list=pLogic->getAllCurrencies();
    fillComboBox(pModelCurrency,list);
}

void ReportWidget::fillDate(){
    std::pair<std::string,std::string> minMax=pLogic->dateMinMax();
    pTimeEditFrom->setDate(QDate::fromString(QString::fromStdString(minMax.first),"yyyy-MM-dd"));
    pTimeEditTo->setDate(QDate::fromString(QString::fromStdString(minMax.second),"yyyy-MM-dd"));
}

void ReportWidget::fillSum(){
    std::pair<double,double> minMax=pLogic->sumMinMax();
    pLineEditSumFrom->setText(QString::number(minMax.first));
    pLineEditSumTo->setText(QString::number(minMax.second));
}

void ReportWidget::fillComboBoxCategory(){
    QObject::disconnect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(categoryChecked(QStandardItem*)));
    std::list<std::string> list=pLogic->getReportCategories(pChbxTypeProfit->isChecked(),pChbxTypeLoss->isChecked());
    fillComboBox(pModelCategory,list);
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(categoryChecked(QStandardItem*)));
}

void ReportWidget::fillComboBoxDescription() {
    std::vector<std::string> listCategories;
    listCategories=getComboBoxCheckedList(pCbxCategory);
    std::list<std::string> listDescriptions;
    listDescriptions=pLogic->getReportDescriptions(listCategories);
    fillComboBox(pModelDescription,listDescriptions);
}

void ReportWidget::fillComboBox(QStandardItemModel* model,std::list<std::string>& list){
    list.insert(list.begin(),"Все");
    model->setRowCount(static_cast<int>(list.size()));
    int row=0;
    for (const auto& i:list){
        QStandardItem* item = new QStandardItem(i.c_str());
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Checked, Qt::CheckStateRole);
        model->setItem(row, 0, item);
        row++;
    }
}

std::vector<std::string> ReportWidget::getComboBoxCheckedList(const QComboBox* combobox) const{
    std::vector<std::string> list;
    for(int i=0; i<combobox->count(); i++){
        QModelIndex index = combobox->model()->index(i, 0);
        if(index.data(Qt::CheckStateRole) == Qt::Checked)
            list.push_back(index.data(Qt::DisplayRole).toString().toStdString());
    }
    return list;
}

void ReportWidget::categoryChecked(QStandardItem* item){
    QObject::disconnect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(categoryChecked(QStandardItem*)));
    checkControl(pModelCategory,item);
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(categoryChecked(QStandardItem*)));
}

void ReportWidget::descriptionChecked(QStandardItem* item){
    QObject::disconnect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(descriptionChecked(QStandardItem*)));
    checkControl(pModelDescription,item);
    QObject::connect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),SLOT(descriptionChecked(QStandardItem*)));
}

void ReportWidget::currencyChecked(QStandardItem* item){
    QObject::disconnect(pModelCurrency,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(currencyChecked(QStandardItem*)));
    checkControl(pModelCurrency,item);
    QObject::connect(pModelCurrency,SIGNAL(itemChanged(QStandardItem*)),SLOT(currencyChecked(QStandardItem*)));
}

void ReportWidget::checkControl(QStandardItemModel* model,QStandardItem* item){
    QModelIndex index = model->index(item->index().row(),0);
    if(item->index().row()==0){
        if(index.data(Qt::CheckStateRole) == Qt::Checked)
            setCheckAll(model,Qt::Checked);
        else
            setCheckAll(model,Qt::Unchecked);
    }
    else{
        if(index.data(Qt::CheckStateRole) == Qt::Unchecked){
            QModelIndex indexAll = model->index(0, 0);
            model->setData(indexAll,Qt::Unchecked, Qt::CheckStateRole);
        }
    }
}

void ReportWidget::setCheckAll(QStandardItemModel* model,Qt::CheckState state){
    for(int i=0; i<model->rowCount(); i++){
        QModelIndex index = model->index(i, 0);
        model->setData(index,state, Qt::CheckStateRole);
    }
}

void ReportWidget::resetFilter(){
    fillFields();
    filter();
}

void ReportWidget::saveTxt(){
    QString fieName = QFileDialog::getSaveFileName(0,tr("Сохранить txt"),"","*.txt");
    pLogic->saveReportTxt(fieName.toStdString(),QDate::currentDate().toString("yyyy-MM-dd").toStdString());
}

void ReportWidget::savePDF(){
    QString fieName = QFileDialog::getSaveFileName(0,tr("Сохранить pdf"),"","*.pdf");
    pLogic->saveReportPDF(fieName.toStdString(),QDate::currentDate().toString("yyyy-MM-dd").toStdString());
}



void ReportWidget::print(){
    QPrinter print;
    QPrintDialog* printDialog=new QPrintDialog(&print);
    if (printDialog->exec() == QDialog::Accepted) {
        // print ...
    }
}

