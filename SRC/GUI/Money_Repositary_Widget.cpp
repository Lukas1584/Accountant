#include "Money_Repositary_Widget.h"


Money_Repositary_Widget::Money_Repositary_Widget(Records_Operations* model, QWidget* parent) : QWidget(parent), pModel(model), isEdit(false)
{
    pTable=new QTableWidget;
    pTable->installEventFilter(this);

    pBtnSave=new QPushButton(tr("Сохранить кошелек"));
    pBtnAdd=new QPushButton(tr("Добавить запись"));
    pBtnEdit=new QPushButton(tr("Редактировать запись"));
    pBtnDelete=new QPushButton(tr("Удалить запись"));
    pBtnCnacel=new QPushButton(tr("Отмена"));

    QObject::connect(pBtnSave,SIGNAL(clicked()),SIGNAL(saveData()));
    QObject::connect(pBtnAdd,SIGNAL(clicked()),SLOT(addRecord()));
    QObject::connect(pBtnDelete,SIGNAL(clicked()),SLOT(deleteRecord()));
    QObject::connect(pBtnEdit,SIGNAL(clicked()),SLOT(editRecord()));
    QObject::connect(pBtnCnacel,SIGNAL(clicked()),SLOT(cancelEditRecord()));

    pTimeEdit=new QDateEdit(QDate::currentDate());
    pCbxType=new QComboBox;
    pCbxType->addItems({tr("Прибыль"),tr("Убыток")});
    pCbxCategory=new QComboBox;
    pCbxCategory->setEditable(true);
    pCbxDescription=new QComboBox;
    pCbxDescription->setEditable(true);
    pLineEditSum=new QLineEdit;
    pCbxCurrency=new QComboBox;
    pCbxCurrency->addItems({"USD","BYR","RUB","EUR"});

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
        row=pModel->rowCount();
    Record_String rec( pTimeEdit->date().toString("yyyy-MM-dd").toStdString(),
                       pCbxType->currentText().toStdString(),
                       pCbxCategory->currentText().toStdString(),
                       pCbxDescription->currentText().toStdString(),
                       pLineEditSum->text().toStdString(),
                       pCbxCurrency->currentText().toStdString());
    pModel->setData(row,rec);
    setWorkView();
    isEdit=false;
    pLineEditSum->clear();
    pModel->sortData();
    dataIsLoaded();
}

void Money_Repositary_Widget::deleteRecord(){
    pModel->removeRow(pTable->selectionModel()->currentIndex().row());
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
    Record_String rec=pModel->data(row);
    pTimeEdit->setDate(QDate::fromString(QString::fromStdString(rec.getDate()),"yyyy-MM-dd"));
    pCbxType->setCurrentText(QString::fromStdString(rec.getType()));
    pCbxCategory->setCurrentText(QString::fromStdString(rec.getCategory()));
    pCbxDescription->setCurrentText(QString::fromStdString(rec.getDescription()));
    pLineEditSum->setText(QString::fromStdString(rec.getSum()));
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
    pCbxCategory->clear();
    updateTable();
    std::list<std::string> categories=pModel->getCategory(pCbxType->currentText().toStdString());
    QStringList categoriesQt;
    for(const auto& i:categories)
        categoriesQt.push_back(QString::fromStdString(i));
    pCbxCategory->addItems(categoriesQt);
    categoryChanged();
}

void Money_Repositary_Widget::categoryChanged(){
    pCbxDescription->clear();
    std::list<std::string> descriptions=pModel->getDescription(pCbxCategory->currentText().toStdString());
    QStringList descriptionsQt;
    for(const auto& i:descriptions)
        descriptionsQt.push_back(QString::fromStdString(i));
    pCbxDescription->addItems(descriptionsQt);
}

void Money_Repositary_Widget::updateTable(){
    int rows=pModel->rowCount();
    int columns=pModel->columnCount();
    pTable->setRowCount(rows);
    pTable->setColumnCount(columns);
    for(int row = 0;row<rows;row++){
        Record_String rec=pModel->data(row);
        QTableWidgetItem* item0 = new QTableWidgetItem(QString::fromStdString(rec.getDate()));
        pTable->setItem(row,0,item0);
        QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(rec.getType()));
        pTable->setItem(row,1,item1);
        QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(rec.getCategory()));
        pTable->setItem(row,2,item2);
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(rec.getDescription()));
        pTable->setItem(row,3,item3);
        QTableWidgetItem* item4 = new QTableWidgetItem(QString::fromStdString(rec.getSum()));
        pTable->setItem(row,4,item4);
        QTableWidgetItem* item5 = new QTableWidgetItem(QString::fromStdString(rec.getCurrency()));
        pTable->setItem(row,5,item5);
    }
    setTableHeader();
    setTableDimensions();
    emit tableChaged();
}

void Money_Repositary_Widget::setTableHeader(){
    std::vector<std::string> header{"Дата","Тип","Категория","Описание","Сумма","Валюта"};
    for(int i=0;i< pModel->columnCount();i++){
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
