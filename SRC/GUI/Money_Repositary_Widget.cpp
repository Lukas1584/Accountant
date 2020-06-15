#include "Money_Repositary_Widget.h"
#include <QBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QHeaderView>
#include <QEvent>


Money_Repositary_Widget::Money_Repositary_Widget(Data_Operations* d) : QWidget(), pDataOperations(d)
{
    pTable=new QTableWidget(3,6);
    QStringList listHeader={tr("Дата"),tr("Тип"),tr("Категория"),tr("Описание"),tr("Сумма"),tr("Валюта")};
    pTable->setHorizontalHeaderLabels(listHeader);
    pTable->verticalHeader()->hide();
    pTable->installEventFilter(this);

    pBtnSave=new QPushButton(tr("Сохранить"));

    QObject::connect(pBtnSave,SIGNAL(clicked()),this,SLOT(save()));



    QLineEdit* pLineEditDate=new QLineEdit;
    //pLineEditDate->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Fixed,QSizePolicy::ToolButton));
    QComboBox* pCbxType=new QComboBox;
    QComboBox* pCbxCategory=new QComboBox;
    QComboBox* pCbxDescription=new QComboBox;
    QLineEdit* pLineEditSum=new QLineEdit;
    QComboBox* pCbxCurrency=new QComboBox;

    QHBoxLayout* pHbxEdit=new QHBoxLayout;
    pHbxEdit->addWidget(pLineEditDate,1);
    pHbxEdit->addWidget(pCbxType,1);
    pHbxEdit->addWidget(pCbxCategory,2);
    pHbxEdit->addWidget(pCbxDescription,3);
    pHbxEdit->addWidget(pLineEditSum,1);
    pHbxEdit->addWidget(pCbxCurrency,1);
    pHbxEdit->addWidget(pBtnSave,1);



    QVBoxLayout* pVbx=new QVBoxLayout;
    pVbx->addWidget(pTable);
    pVbx->addLayout(pHbxEdit);
    setLayout(pVbx);


}




bool Money_Repositary_Widget::eventFilter(QObject *pObject, QEvent *pEvent){
    if(pEvent->type() == QEvent::Resize){
        pTable->setColumnWidth(0, pTable->width() * 0.1);
        pTable->setColumnWidth(1, pTable->width() * 0.1);
        pTable->setColumnWidth(2, pTable->width() * 0.3);
        pTable->setColumnWidth(3, pTable->width() * 0.3);
        pTable->setColumnWidth(4, pTable->width() * 0.1);
        pTable->setColumnWidth(5, pTable->width() * 0.1);
    }
    return false;
}

void Money_Repositary_Widget::save(){
    emit saveData();
}

void Money_Repositary_Widget::dataIsLoaded(){

    QStringList data=pDataOperations->getData();
    pTable->setRowCount(data.size()/7);
    auto rec=data.begin();
    for(int row=0; row!=pTable->rowCount(); row++){
        for(int column=0; column!=pTable->columnCount();column++,rec++){
            QTableWidgetItem* newItem = new QTableWidgetItem();
            newItem->setText(*rec);
            pTable->setItem(row, column, newItem);
        }
    }
}
