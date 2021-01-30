#include "MoneyRepositaryWidget.h"

MoneyRepositaryWidget::MoneyRepositaryWidget(std::shared_ptr<AbstractBusinessLogic> logic, QWidget* parent):
    QWidget(parent),pLogic(logic){
    drawWindow();
    connectButtons();
    setWorkView();
}

void MoneyRepositaryWidget::drawWindow(){
    pTable=new QTableWidget;
    pTable->installEventFilter(this);

    pBtnSave=new QPushButton(tr("Сохранить кошелек"));
    pBtnAdd=new QPushButton(tr("Добавить запись"));
    pBtnEdit=new QPushButton(tr("Редактировать запись"));
    pBtnDelete=new QPushButton(tr("Удалить запись"));
    pBtnCnacel=new QPushButton(tr("Отмена"));

    pTimeEdit=new QDateEdit(QDate::currentDate());
    pCbxType=new QComboBox;
    pCbxType->addItems(convertToQList(pLogic->getAllTypes()));
    pCbxCategory=new QComboBox;
    pCbxCategory->setEditable(true);
    pCbxDescription=new QComboBox;
    pCbxDescription->setEditable(true);
    pLineEditSum=new QLineEdit;
    pCbxCurrency=new QComboBox;
    pCbxCurrency->addItems(convertToQList(pLogic->getAllCurrencies()));

    QHBoxLayout* pHbxEdit=new QHBoxLayout;
    pHbxEdit->addWidget(pTimeEdit,1);
    pHbxEdit->addWidget(pCbxType,1);
    pHbxEdit->addWidget(pCbxCategory,3);
    pHbxEdit->addWidget(pCbxDescription,3);
    pHbxEdit->addWidget(pLineEditSum,1);
    pHbxEdit->addWidget(pCbxCurrency,1);

    QVBoxLayout* pVbxTable=new QVBoxLayout;
    pVbxTable->addWidget(pTable);
    pVbxTable->addLayout(pHbxEdit);

    QVBoxLayout* pVbxButtons=new QVBoxLayout;
    pVbxButtons->addStretch(1);
    pVbxButtons->addWidget(pBtnSave);
    pVbxButtons->addSpacing(10);
    pVbxButtons->addWidget(pBtnDelete);
    pVbxButtons->addWidget(pBtnEdit);
    pVbxButtons->addWidget(pBtnCnacel);
    pVbxButtons->addSpacing(10);
    pVbxButtons->addWidget(pBtnAdd);

    QHBoxLayout* pHbxMain=new QHBoxLayout;
    pHbxMain->addLayout(pVbxTable);
    pHbxMain->addLayout(pVbxButtons);

    setLayout(pHbxMain);
}

void MoneyRepositaryWidget::connectButtons(){
    QObject::connect(pBtnSave,SIGNAL(clicked()),SLOT(saveData()));
    QObject::connect(pBtnAdd,SIGNAL(clicked()),SLOT(addRecord()));
    QObject::connect(pBtnDelete,SIGNAL(clicked()),SLOT(deleteRecord()));
    QObject::connect(pBtnEdit,SIGNAL(clicked()),SLOT(editRecord()));
    QObject::connect(pBtnCnacel,SIGNAL(clicked()),SLOT(cancelEditRecord()));
    QObject::connect(pCbxType,SIGNAL(textActivated(const QString&)),SLOT(updateCbxCategory()));
    QObject::connect(pCbxCategory,SIGNAL(textActivated(const QString&)),SLOT(categoryChanged()));
}

bool MoneyRepositaryWidget::eventFilter(QObject*, QEvent *pEvent){
    if(pEvent->type() == QEvent::Resize)
        setTableDimensions();
    return false;
}

void MoneyRepositaryWidget::addRecord(){
    unsigned int row=0;
    if(isEdit)
        row=pTable->selectionModel()->currentIndex().row();
    else
        row=pLogic->rowsCount();
    RecordString rec( pTimeEdit->date().toString("yyyy-MM-dd").toStdString(),
                       pCbxType->currentText().toStdString(),
                       pCbxCategory->currentText().toStdString(),
                       pCbxDescription->currentText().toStdString(),
                       pLineEditSum->text().toDouble(),
                       pCbxCurrency->currentText().toStdString());
    pLogic->setData(row,rec);
    pLogic->sortData();
    isEdit=false;
    pLineEditSum->clear();
    setWorkView();
    dataIsLoaded();
}

void MoneyRepositaryWidget::deleteRecord(){
    pLogic->removeRow(pTable->selectionModel()->currentIndex().row());
    dataIsLoaded();
}

void MoneyRepositaryWidget::editRecord(){
    isEdit=true;
    setEditView();
}

void MoneyRepositaryWidget::setEditView(){
    pBtnCnacel->setEnabled(true);
    pBtnSave->setEnabled(false);
    pBtnEdit->setEnabled(false);
    pBtnDelete->setEnabled(false);
    pBtnAdd->setText(tr("Сохранить изменения"));
    unsigned int row=0;
    if(pTable->selectionModel()->hasSelection()) row=pTable->selectionModel()->currentIndex().row();
    RecordString rec=pLogic->getData(row);
    pTimeEdit->setDate(QDate::fromString(QString::fromStdString(rec.getDate()),"yyyy-MM-dd"));
    pCbxType->setCurrentText(QString::fromStdString(rec.getType()));
    pCbxCategory->setCurrentText(QString::fromStdString(rec.getCategory()));
    pCbxDescription->setCurrentText(QString::fromStdString(rec.getDescription()));
    pLineEditSum->setText(QString::number(rec.getSum()));
    pCbxCurrency->setCurrentText(QString::fromStdString(rec.getCurrency()));
}

void MoneyRepositaryWidget::setWorkView(){
    pBtnCnacel->setEnabled(false);
    pBtnSave->setEnabled(true);
    pBtnEdit->setEnabled(true);
    pBtnDelete->setEnabled(true);
    pBtnAdd->setText(tr("Добавить запись"));
}

void MoneyRepositaryWidget::cancelEditRecord(){
    isEdit=false;
    setWorkView();
}

void MoneyRepositaryWidget::dataIsLoaded(){
    updateTable();
    pTimeEdit->setDate(QDate::currentDate());
    updateCbxCategory();
    emit tableChanged();
}

void MoneyRepositaryWidget::updateCbxCategory(){
    pCbxCategory->clear();
    pCbxCategory->addItems(convertToQList(pLogic->getDataCategories(pCbxType->currentText().toStdString())));
    categoryChanged();
}

QStringList MoneyRepositaryWidget::convertToQList(const std::list<std::string>& list) const{
    QStringList qList;
    for(const auto& i:list)
        qList.push_back(QString::fromStdString(i));
    return qList;
}

void MoneyRepositaryWidget::categoryChanged(){
    pCbxDescription->clear();
    pCbxDescription->addItems(convertToQList(pLogic->getDataDescriptions(pCbxCategory->currentText().toStdString())));
}

void MoneyRepositaryWidget::updateTable(){
    unsigned int rows=pLogic->rowsCount();
    pTable->setRowCount(rows);
    pTable->setColumnCount(pLogic->columnsCount());
    for(unsigned int row = 0; row<rows; row++){
        RecordString rec=pLogic->getData(row);
        QTableWidgetItem* item0 = new QTableWidgetItem(QString::fromStdString(rec.getDate()));
        pTable->setItem(row,0,item0);
        QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(rec.getType()));
        pTable->setItem(row,1,item1);
        QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(rec.getCategory()));
        pTable->setItem(row,2,item2);
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(rec.getDescription()));
        pTable->setItem(row,3,item3);
        QTableWidgetItem* item4 = new QTableWidgetItem(QString::number(rec.getSum()));
        pTable->setItem(row,4,item4);
        QTableWidgetItem* item5 = new QTableWidgetItem(QString::fromStdString(rec.getCurrency()));
        pTable->setItem(row,5,item5);
    }
    setTableHeader();
    setTableDimensions();
}

void MoneyRepositaryWidget::setTableHeader(){
    std::vector<std::string> header{"Дата","Тип","Категория","Описание","Сумма","Валюта"};
    int columnsCount=header.size();
    for(int i=0;i<columnsCount;i++){
        QTableWidgetItem* item=new QTableWidgetItem(header[i].c_str());
        pTable->setHorizontalHeaderItem(i,item);
    }
    pTable->verticalHeader()->hide();
}

void MoneyRepositaryWidget::setTableDimensions(){
    pTable->setColumnWidth(0, pTable->width() * 0.1);
    pTable->setColumnWidth(1, pTable->width() * 0.1);
    pTable->setColumnWidth(2, pTable->width() * 0.28);
    pTable->setColumnWidth(3, pTable->width() * 0.3);
    pTable->setColumnWidth(4, pTable->width() * 0.1);
    pTable->setColumnWidth(5, pTable->width() * 0.1);
}

void MoneyRepositaryWidget::saveData(){
    pLogic->saveData();
}
