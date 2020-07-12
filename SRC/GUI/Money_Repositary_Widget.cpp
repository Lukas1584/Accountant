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
    if(pEvent->type() == QEvent::Resize){
        setTableDimensions();
    }
    return false;
}

void Money_Repositary_Widget::addRecord(){
    int row;
    if(isEdit){
        row=pTable->selectionModel()->currentIndex().row();
    }
    else{
        row=pModel->rowCount();
        pModel->insertRows(row,1);
    }
    pModel->setData(row,0, pTimeEdit->date().toString("yyyy-MM-dd").toStdString());
    pModel->setData(row,1,pCbxType->currentText().toStdString());
    pModel->setData(row,2,pCbxCategory->currentText().toStdString());
    pModel->setData(row,3,pCbxDescription->currentText().toStdString());
    pModel->setData(row,4,pLineEditSum->text().toStdString());
    pModel->setData(row,5,pCbxCurrency->currentText().toStdString());
    setWorkView();
    isEdit=false;
    pLineEditSum->clear();
    pModel->sortData();
    dataIsLoaded();
}

void Money_Repositary_Widget::deleteRecord(){
    pModel->removeRows(pTable->selectionModel()->currentIndex().row());
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
    pTimeEdit->setDate(QDate::fromString(QString::fromStdString(pModel->data(row,0)),"yyyy-MM-dd"));
    pCbxType->setCurrentText(QString::fromStdString(pModel->data(row,1)));
    pCbxCategory->setCurrentText(QString::fromStdString(pModel->data(row,2)));
    pCbxDescription->setCurrentText(QString::fromStdString(pModel->data(row,3)));
    pLineEditSum->setText(QString::fromStdString(pModel->data(row,4)));
    pCbxCurrency->setCurrentText(QString::fromStdString(pModel->data(row,5)));
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
    std::list<std::string> categories=pModel->getCategoryOrDescription(pCbxType->currentText().toStdString(),"category");
    QStringList categoriesQt;
    for(auto i:categories){
        categoriesQt.push_back(QString::fromStdString(i));
    }
    pCbxCategory->addItems(categoriesQt);
    categoryChanged();
}

void Money_Repositary_Widget::categoryChanged(){
    pCbxDescription->clear();
    std::list<std::string> descriptions=pModel->getCategoryOrDescription(pCbxCategory->currentText().toStdString(),"description");
    QStringList descriptionsQt;
    for(auto i:descriptions){
        descriptionsQt.push_back(QString::fromStdString(i));
    }
    pCbxDescription->addItems(descriptionsQt);
}

void Money_Repositary_Widget::updateTable(){
    int rows=pModel->rowCount();
    int columns=pModel->columnCount();
    pTable->setRowCount(rows);
    pTable->setColumnCount(columns);
    for(int row = 0;row<rows;row++){
        for(int column = 0;column<columns;column++){
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(pModel->data(row,column)));
            pTable->setItem(row,column,item);
        }
    }
    setTableHeader();
    setTableDimensions();
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
