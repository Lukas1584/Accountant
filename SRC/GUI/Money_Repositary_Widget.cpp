#include "Money_Repositary_Widget.h"
#include <QBoxLayout>
#include <QComboBox>
#include <QLineEdit>

Money_Repositary_Widget::Money_Repositary_Widget(Data_Operations* d) : QWidget(), pDataOperations(d)
{
    pTable=new QTableWidget(3,6);
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



    QVBoxLayout* pVbx=new QVBoxLayout;
    pVbx->addWidget(pTable);
    pVbx->addLayout(pHbxEdit);
    setLayout(pVbx);

    for(int row=0; row!=pTable->rowCount(); ++row){
        for(int column=0; column!=pTable->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg((row+1)*(column+1)));
            pTable->setItem(row, column, newItem);
        }
    }


}
