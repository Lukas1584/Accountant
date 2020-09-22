#include "Money_Repositary_Widget.h"

Money_Repositary_Widget::Money_Repositary_Widget(std::shared_ptr<AbstractBusinessLogic> logic, QWidget* parent):
    QWidget(parent),pLogic(logic){
    pTable=new QTableWidget;
    pTable->installEventFilter(this);

    pBtnSave=new QPushButton(tr("Сохранить кошелек"));
    pBtnAdd=new QPushButton(tr("Добавить запись"));
    pBtnEdit=new QPushButton(tr("Редактировать запись"));
    pBtnDelete=new QPushButton(tr("Удалить запись"));
    pBtnCnacel=new QPushButton(tr("Отмена"));

    QObject::connect(pBtnSave,SIGNAL(clicked()),SLOT(saveData()));
    QObject::connect(pBtnAdd,SIGNAL(clicked()),SLOT(addRecord()));
    QObject::connect(pBtnDelete,SIGNAL(clicked()),SLOT(deleteRecord()));
    QObject::connect(pBtnEdit,SIGNAL(clicked()),SLOT(editRecord()));
    QObject::connect(pBtnCnacel,SIGNAL(clicked()),SLOT(cancelEditRecord()));

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

    QObject::connect(pCbxType,SIGNAL(textActivated(const QString&)),SLOT(dataIsLoaded()));
    QObject::connect(pCbxCategory,SIGNAL(textActivated(const QString&)),SLOT(categoryChanged()));

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
    setWorkView();
}

bool Money_Repositary_Widget::eventFilter(QObject*, QEvent *pEvent){
    if(pEvent->type() == QEvent::Resize)
        setTableDimensions();
    return false;
}

void Money_Repositary_Widget::addRecord(){
    int row=-1;
    if(isEdit)
        row=pTable->selectionModel()->currentIndex().row();
    else
        row=pLogic->rowsCount();
    Record_String rec( pTimeEdit->date().toString("yyyy-MM-dd").toStdString(),
                       pCbxType->currentText().toStdString(),
                       pCbxCategory->currentText().toStdString(),
                       pCbxDescription->currentText().toStdString(),
                       pLineEditSum->text().toDouble(),
                       pCbxCurrency->currentText().toStdString());
    pLogic->setData(row,rec);
    setWorkView();
    isEdit=false;
    pLineEditSum->clear();
    pLogic->sortData();
    dataIsLoaded();
}

void Money_Repositary_Widget::deleteRecord(){
    pLogic->removeRow(pTable->selectionModel()->currentIndex().row());
    dataIsLoaded();
}

void Money_Repositary_Widget::editRecord(){
    isEdit=true;
    setEditView();
}

void Money_Repositary_Widget::setEditView(){
    pBtnCnacel->setEnabled(true);
    pBtnSave->setEnabled(false);
    pBtnEdit->setEnabled(false);
    pBtnDelete->setEnabled(false);
    pBtnAdd->setText(tr("Сохранить изменения"));
    int row=pTable->selectionModel()->currentIndex().row();
    Record_String rec=pLogic->getData(row);
    pTimeEdit->setDate(QDate::fromString(QString::fromStdString(rec.getDate()),"yyyy-MM-dd"));
    pCbxType->setCurrentText(QString::fromStdString(rec.getType()));
    pCbxCategory->setCurrentText(QString::fromStdString(rec.getCategory()));
    pCbxDescription->setCurrentText(QString::fromStdString(rec.getDescription()));
    pLineEditSum->setText(QString::number(rec.getSum()));
    pCbxCurrency->setCurrentText(QString::fromStdString(rec.getCurrency()));
}

void Money_Repositary_Widget::setWorkView(){
    pBtnCnacel->setEnabled(false);
    pBtnSave->setEnabled(true);
    pBtnEdit->setEnabled(true);
    pBtnDelete->setEnabled(true);
    pBtnAdd->setText(tr("Добавить запись"));
}

void Money_Repositary_Widget::cancelEditRecord(){
    isEdit=false;
    setWorkView();
}

void Money_Repositary_Widget::dataIsLoaded(){
    updateTable();
    pCbxCategory->clear();
    pCbxCategory->addItems(convertToQList(pLogic->getDataCategories(pCbxType->currentText().toStdString())));
    categoryChanged();
    emit tableChanged();
}

QStringList Money_Repositary_Widget::convertToQList(const std::list<std::string>& list){
    QStringList qList;
    for(const auto& i:list)
        qList.push_back(QString::fromStdString(i));
    return qList;
}

void Money_Repositary_Widget::categoryChanged(){
    pCbxDescription->clear();
    pCbxDescription->addItems(convertToQList(pLogic->getDataDescriptions(pCbxCategory->currentText().toStdString())));
}

void Money_Repositary_Widget::updateTable(){
    int rows=pLogic->rowsCount();
    int columns=pLogic->columnsCount();
    pTable->setRowCount(rows);
    pTable->setColumnCount(columns);
    for(int row = 0;row<rows;row++){
        Record_String rec=pLogic->getData(row);
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

void Money_Repositary_Widget::setTableHeader(){
    std::vector<std::string> header{"Дата","Тип","Категория","Описание","Сумма","Валюта"};
    for(int i=0;i< pLogic->columnsCount();i++){
        QTableWidgetItem* item=new QTableWidgetItem(header[i].c_str());
        pTable->setHorizontalHeaderItem(i,item);
    }
    pTable->verticalHeader()->hide();
}

void Money_Repositary_Widget::setTableDimensions(){
    pTable->setColumnWidth(0, pTable->width() * 0.1);
    pTable->setColumnWidth(1, pTable->width() * 0.1);
    pTable->setColumnWidth(2, pTable->width() * 0.28);
    pTable->setColumnWidth(3, pTable->width() * 0.3);
    pTable->setColumnWidth(4, pTable->width() * 0.1);
    pTable->setColumnWidth(5, pTable->width() * 0.1);
}

void Money_Repositary_Widget::saveData(){
    pLogic->saveData();
}
