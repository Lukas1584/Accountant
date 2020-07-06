#include "Report_Widget.h"


Report_Widget::Report_Widget(std::shared_ptr<Report> report) : QWidget(),pReport(report)
{
    pTable=new QTableWidget(this);
    pTable->installEventFilter(this);

    //QStringList header{tr("Дата"),tr("Тип"),tr("Категория"),tr("Описание"),tr("Сумма"),tr("Валюта")};
    //pTable->setHorizontalHeaderLabels(header);


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
    pTimeEditTo=new QDateEdit(QDate::currentDate());
    QVBoxLayout* pVbxDate=new QVBoxLayout;
    pVbxDate->addWidget(pLblDateFrom);
    pVbxDate->addWidget(pTimeEditFrom);
    pVbxDate->addWidget(pLblDateTo);
    pVbxDate->addWidget(pTimeEditTo);
    pVbxDate->addStretch(1);

    QLabel* pLblType=new QLabel(tr("Тип:"));
    pChbxTypeProfit=new QCheckBox(tr("Прибыль"));
    pChbxTypeProfit->setChecked(true);
    pChbxTypeLoss=new QCheckBox(tr("Убыток"));
    pChbxTypeLoss->setChecked(true);
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
    pChbxUsd->setChecked(true);
    pChbxByr=new QCheckBox(tr("BYR"));
    pChbxByr->setChecked(true);
    pChbxRub=new QCheckBox(tr("RUB"));
    pChbxRub->setChecked(true);
    pChbxEur=new QCheckBox(tr("EUR"));
    pChbxEur->setChecked(true);
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
    QObject::connect(pCbxCategory->model(),SIGNAL(itemChanged(QStandardItem*)),SLOT(fillComboBoxDescription()));
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
    fillComboBoxCategory();
}

bool Report_Widget::eventFilter(QObject *pObject, QEvent *pEvent){
    Q_UNUSED(pObject);
    Q_UNUSED(pEvent);
    if(pEvent->type() == QEvent::Resize ){
        pTable->setColumnWidth(0, pTable->width() * 0.1);
        pTable->setColumnWidth(1, pTable->width() * 0.1);
        pTable->setColumnWidth(2, pTable->width() * 0.295);
        pTable->setColumnWidth(3, pTable->width() * 0.3);
        pTable->setColumnWidth(4, pTable->width() * 0.1);
        pTable->setColumnWidth(5, pTable->width() * 0.1);
    }
    return false;
}

void Report_Widget::filter(){
    QVariant from=pTimeEditFrom->date();
    QVariant to=pTimeEditTo->date();

    pReport->filterDB(from.toString().toStdString(),
                      to.toString().toStdString(),
                      typeToReport(),
                      getComboBoxCheckedList(pCbxCategory),
                      getComboBoxCheckedList(pCbxDescription),
                      pLineEditSumFrom->text().toFloat(),
                      pLineEditSumTo->text().toFloat(),
                      currencyToReport());
    updateTable();
}

int Report_Widget::typeToReport(){
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

std::vector<bool> Report_Widget::currencyToReport(){
    std::vector<bool> currency(4);
    if(pChbxUsd->isChecked())
        currency[0]= true;
    else currency[0]= false;
    if(pChbxByr->isChecked())
        currency[1]= true;
    else currency[1]= false;
    if(pChbxRub->isChecked())
        currency[2]= true;
    else currency [2]= false;
    if(pChbxEur->isChecked())
        currency[3]= true;
    else currency [3]= false;
    return currency;
}

void Report_Widget::fillComboBoxCategory(){
    std::list<std::string> list;
    list=pReport->getCategories(pChbxTypeProfit->isChecked(),pChbxTypeLoss->isChecked());
    pModelCategory->setRowCount(list.size());
    int j=0;
    for (auto i:list)
    {
        QStandardItem* item = new QStandardItem(i.c_str());
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
        item->setData(Qt::Checked, Qt::CheckStateRole);
        pModelCategory->setItem(j, 0, item);
        j++;
    }
    fillComboBoxDescription();
}

void Report_Widget::fillComboBoxDescription(){
    std::vector<std::string> listCategories;
    listCategories=getComboBoxCheckedList(pCbxCategory);
    std::list<std::string> listDescriptions;
    listDescriptions=pReport->getDescriptions(listCategories);
    pModelDescription->setRowCount(listDescriptions.size());
    int j=0;
    for (auto i:listDescriptions){
        QStandardItem* item = new QStandardItem(i.c_str());
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Checked, Qt::CheckStateRole);
        pModelDescription->setItem(j, 0, item);
        j++;
    }
}

std::vector<std::string> Report_Widget::getComboBoxCheckedList(const QComboBox* combobox){
    std::vector<std::string> list;
    for(int i=0; i<combobox->count(); i++){
        QModelIndex index = combobox->model()->index(i, 0);
        if(index.data(Qt::CheckStateRole).toInt() == 2)
            list.push_back(index.data(Qt::DisplayRole).toString().toStdString());
    }
    return list;
}

