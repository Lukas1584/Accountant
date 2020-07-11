#include "Report_Widget.h"

Report_Widget::Report_Widget(Report *report, QWidget *parent) : QWidget(parent),pReport(report){
    pTable=new QTableWidget(this);
    pTable->installEventFilter(this);

    pBtnSaveTxt=new QPushButton(tr("Сохранить как"));
    pBtnSaveExcel=new QPushButton(tr("Сохранить в Excel"));
    pBtnPrint=new QPushButton(tr("Печать"));
    pBtnChart=new QPushButton(tr("График"));
    pBtnApply=new QPushButton(tr("Применить фильтр"));
    pBtnReset=new QPushButton(tr("Сбросить фильтр"));

    QVBoxLayout* pVbxButtons=new QVBoxLayout;
    pVbxButtons->addWidget(pBtnSaveTxt);
    pVbxButtons->addWidget(pBtnSaveExcel);
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
    pChbxUsd=new QCheckBox(tr("USD"));
    pChbxByr=new QCheckBox(tr("BYR"));
    pChbxRub=new QCheckBox(tr("RUB"));
    pChbxEur=new QCheckBox(tr("EUR"));
    QVBoxLayout* pVbxCurrency=new QVBoxLayout;
    pVbxCurrency->addWidget(pLblCurrency);
    pVbxCurrency->addWidget(pChbxUsd);
    pVbxCurrency->addWidget(pChbxByr);
    pVbxCurrency->addWidget(pChbxRub);
    pVbxCurrency->addWidget(pChbxEur);
    pVbxCurrency->addStretch(1);

    QHBoxLayout* pHbxFilter=new QHBoxLayout;
    pHbxFilter->addLayout(pVbxDate,2);
    pHbxFilter->addLayout(pVbxType,1);
    pHbxFilter->addLayout(pVbxCategory,4);
    pHbxFilter->addLayout(pVbxDescription,4);
    pHbxFilter->addLayout(pVbxSum,2);
    pHbxFilter->addLayout(pVbxCurrency,1);

    QHBoxLayout* pHbxButtonsFilter=new QHBoxLayout;
    pHbxButtonsFilter->addWidget(pBtnApply);
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

    QObject::connect(pBtnApply,SIGNAL(clicked()),SLOT(filter()));
    QObject::connect(pChbxTypeProfit,SIGNAL(clicked()),SLOT(fillComboBoxCategory()));
    QObject::connect(pChbxTypeLoss,SIGNAL(clicked()),SLOT(fillComboBoxCategory()));
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(categoryChecked(QStandardItem*)));
    QObject::connect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),SLOT(descriptionChecked(QStandardItem*)));
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(fillComboBoxDescription()));
    QObject::connect(pBtnReset,SIGNAL(clicked()),SLOT(resetFilter()));
}

void Report_Widget::updateTable(){
    int rows=pReport->rowCount();
    int columns=pReport->columnCount();
    pTable->setRowCount(rows);
    pTable->setColumnCount(columns);
    for(int row = 0;row<rows;row++){
        std::vector<std::string> rowData=pReport->getRow(row);
        for(int column = 0;column<columns;column++){
            QTableWidgetItem* item = new QTableWidgetItem(rowData[column].c_str());
            pTable->setItem(row,column,item);
        }
    }
    setTableHeader();
    setTableDimensions();
}

void Report_Widget::setTableHeader(){
    std::vector<std::string> header{"Дата","Тип","Категория","Описание","Сумма","Валюта"};
    for(int i=0;i< pReport->columnCount();i++){
        QTableWidgetItem* item=new QTableWidgetItem(header[i].c_str());
        pTable->setHorizontalHeaderItem(i,item);
    }
    pTable->verticalHeader()->hide();
}

void Report_Widget::setTableDimensions(){
    pTable->setColumnWidth(0, pTable->width() * 0.1);
    pTable->setColumnWidth(1, pTable->width() * 0.1);
    pTable->setColumnWidth(2, pTable->width() * 0.3);
    pTable->setColumnWidth(3, pTable->width() * 0.3);
    pTable->setColumnWidth(4, pTable->width() * 0.1);
    pTable->setColumnWidth(5, pTable->width() * 0.1);
}

bool Report_Widget::eventFilter(QObject* , QEvent *pEvent){
    if(pEvent->type() == QEvent::Resize )
        setTableDimensions();
    return false;
}

void Report_Widget::filter(){
    pReport->filterDB(pTimeEditFrom->date().toString("yyyy-MM-dd").toStdString(),
                      pTimeEditTo->date().toString("yyyy-MM-dd").toStdString(),
                      typeToReport(),
                      getComboBoxCheckedList(pCbxCategory),
                      getComboBoxCheckedList(pCbxDescription),
                      pLineEditSumFrom->text().toFloat(),
                      pLineEditSumTo->text().toFloat(),
                      currencyToReport());
    updateTable();
}

int Report_Widget::typeToReport() const{
    if (pChbxTypeProfit->isChecked()){
            if(pChbxTypeLoss->isChecked()) {
                return 11;
            }
            else return 10;
    }
    else {
        if(pChbxTypeLoss->isChecked()) {
            return 01;
        }
        else return 00;
    }
}

std::vector<bool> Report_Widget::currencyToReport() const{
    int usd=0;
    int byr=1;
    int rub=2;
    int eur=3;
    std::vector<bool> currency(4);
    if(pChbxUsd->isChecked())
        currency[usd]= true;
    else currency[usd]= false;
    if(pChbxByr->isChecked())
        currency[byr]= true;
    else currency[byr]= false;
    if(pChbxRub->isChecked())
        currency[rub]= true;
    else currency [rub]= false;
    if(pChbxEur->isChecked())
        currency[eur]= true;
    else currency [eur]= false;
    return currency;
}

void Report_Widget::fillFields(){
    pChbxTypeProfit->setChecked(true);
    pChbxTypeLoss->setChecked(true);
    fillComboBoxCategory();
    fillComboBoxDescription();
    fillDate();
    fillSum();
    pChbxUsd->setChecked(true);
    pChbxByr->setChecked(true);
    pChbxRub->setChecked(true);
    pChbxEur->setChecked(true);
}

void Report_Widget::fillDate(){
    std::pair<std::string,std::string> minMax=pReport->dateMinMax();
    pTimeEditFrom->setDate(QDate::fromString(QString::fromStdString(minMax.first),"yyyy-MM-dd"));
    pTimeEditTo->setDate(QDate::fromString(QString::fromStdString(minMax.second),"yyyy-MM-dd"));
}

void Report_Widget::fillSum(){
    std::pair<std::string,std::string> minMax=pReport->sumMinMax();
    pLineEditSumFrom->setText(QString::fromStdString(minMax.first));
    pLineEditSumTo->setText(QString::fromStdString(minMax.second));
}

void Report_Widget::fillComboBoxCategory(){
    QObject::disconnect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(categoryChecked(QStandardItem*)));
    std::list<std::string> list;
    list=pReport->getCategories(pChbxTypeProfit->isChecked(),pChbxTypeLoss->isChecked());
    list.insert(list.begin(),"Все");
    pModelCategory->setRowCount(static_cast<int>(list.size()));
    int row=0;
    for (auto i:list){
        QStandardItem* item = new QStandardItem(i.c_str());
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
        item->setData(Qt::Checked, Qt::CheckStateRole);
        pModelCategory->setItem(row, 0, item);
        row++;
    }
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(categoryChecked(QStandardItem*)));
}

void Report_Widget::fillComboBoxDescription() {

    std::vector<std::string> listCategories;
    listCategories=getComboBoxCheckedList(pCbxCategory);
    std::list<std::string> listDescriptions;
    listDescriptions=pReport->getDescriptions(listCategories);
    listDescriptions.insert(listDescriptions.begin(),"Все");
    pModelDescription->setRowCount(static_cast<int>(listDescriptions.size()));
    int row=0;
    for (auto i:listDescriptions){
        QStandardItem* item = new QStandardItem(i.c_str());
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Checked, Qt::CheckStateRole);
        pModelDescription->setItem(row, 0, item);
        row++;
    }

}

std::vector<std::string> Report_Widget::getComboBoxCheckedList(const QComboBox* combobox) const{
    std::vector<std::string> list;
    for(int i=0; i<combobox->count(); i++){
        QModelIndex index = combobox->model()->index(i, 0);
        if(index.data(Qt::CheckStateRole) == Qt::Checked)
            list.push_back(index.data(Qt::DisplayRole).toString().toStdString());
    }
    return list;
}

void Report_Widget::categoryChecked(QStandardItem* item){
    QObject::disconnect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(categoryChecked(QStandardItem*)));
    checkControl(pModelCategory,item);
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(categoryChecked(QStandardItem*)));
}

void Report_Widget::descriptionChecked(QStandardItem* item){
    QObject::disconnect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(descriptionChecked(QStandardItem*)));
    checkControl(pModelDescription,item);
    QObject::connect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),SLOT(descriptionChecked(QStandardItem*)));
}

void Report_Widget::checkControl(QStandardItemModel* model,QStandardItem* item){
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

void Report_Widget::setCheckAll(QStandardItemModel* model,Qt::CheckState state){
    for(int i=0; i<model->rowCount(); i++){
        QModelIndex index = model->index(i, 0);
        model->setData(index,state, Qt::CheckStateRole);
    }
}

void Report_Widget::resetFilter(){
    fillFields();
    filter();
}




