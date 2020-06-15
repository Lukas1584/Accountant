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
    pBtnAdd=new QPushButton(tr("Добавить"));
    pBtnEdit=new QPushButton(tr("Редактировать"));
    pBtnDelete=new QPushButton(tr("Удалить"));

    QObject::connect(pBtnSave,SIGNAL(clicked()),this,SLOT(save()));

    pLineEditDate=new QLineEdit;
    pCbxType=new QComboBox;
    pCbxType->addItems({tr("Доход"),tr("Убыток")});
    pCbxCategory=new QComboBox;
    pCbxDescription=new QComboBox;
    pLineEditSum=new QLineEdit;
    pCbxCurrency=new QComboBox;
    pCbxCurrency->addItems({"USD","BYR","RUB","EUR"});

    QHBoxLayout* pHbxEdit=new QHBoxLayout;
    pHbxEdit->addWidget(pLineEditDate,1);
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
    pVbxButtons->addWidget(pBtnDelete);
    pVbxButtons->addSpacing(10);
    pVbxButtons->addWidget(pBtnEdit);
    pVbxButtons->addWidget(pBtnSave);
    pVbxButtons->addSpacing(10);
    pVbxButtons->addWidget(pBtnAdd);



    QHBoxLayout* pHbxMain=new QHBoxLayout;
    pHbxMain->addLayout(pVbxTable);
    pHbxMain->addLayout(pVbxButtons);


    setLayout(pHbxMain);
}




bool Money_Repositary_Widget::eventFilter(QObject *pObject, QEvent *pEvent){
    Q_UNUSED(pObject);
    Q_UNUSED(pEvent);
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
