#include "Money_Repositary_Widget.h"

Money_Repositary_Widget::Money_Repositary_Widget(QAbstractTableModel* model) : QWidget(), pModel(model)
{
    pTable=new QTableView;
    pTable->setModel(pModel);
    pTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    pTable->installEventFilter(this);

    pBtnSave=new QPushButton(tr("Сохранить кошелек"));
    pBtnAdd=new QPushButton(tr("Добавить запись"));
    pBtnEdit=new QPushButton(tr("Редактировать запись"));
    pBtnDelete=new QPushButton(tr("Удалить запись"));
    pBtnCnacel=new QPushButton(tr("Отмена"));
    setWorkView();

    QObject::connect(pBtnSave,SIGNAL(clicked()),SLOT(save()));
    QObject::connect(pBtnAdd,SIGNAL(clicked()),SLOT(addRecord()));
    QObject::connect(pBtnDelete,SIGNAL(clicked()),SLOT(deleteRecord()));
    QObject::connect(pBtnEdit,SIGNAL(clicked()),SLOT(editRecord()));
    QObject::connect(pBtnCnacel,SIGNAL(clicked()),SLOT(cancelEditRecord()));

    pLineEditDate=new QLineEdit;
    pCbxType=new QComboBox;
    pCbxType->addItems({tr("Прибыль"),tr("Убыток")});
    pCbxCategory=new QComboBox;
    pCbxDescription=new QComboBox;
    pLineEditSum=new QLineEdit;
    pCbxCurrency=new QComboBox;
    pCbxCurrency->addItems({"USD","BYR","RUB","EUR"});

    ///временно
    pCbxCategory->addItems({tr("Временная категория"),tr("Категория временная")});
    pCbxDescription->addItems({tr("Временное описание"),tr("Описание временное")});

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

bool Money_Repositary_Widget::eventFilter(QObject *pObject, QEvent *pEvent){
    Q_UNUSED(pObject);
    Q_UNUSED(pEvent);
    if(pEvent->type() == QEvent::Resize){
        pTable->setColumnWidth(0, pTable->width() * 0.1);
        pTable->setColumnWidth(1, pTable->width() * 0.1);
        pTable->setColumnWidth(2, pTable->width() * 0.295);
        pTable->setColumnWidth(3, pTable->width() * 0.3);
        pTable->setColumnWidth(4, pTable->width() * 0.1);
        pTable->setColumnWidth(5, pTable->width() * 0.1);
    }
    return false;
}

void Money_Repositary_Widget::save(){
    emit saveData();
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
    pModel->setData(pModel->index(row,0),pLineEditDate->text());
    pModel->setData(pModel->index(row,1),pCbxType->currentText());
    pModel->setData(pModel->index(row,2),pCbxCategory->currentText());
    pModel->setData(pModel->index(row,3),pCbxDescription->currentText());
    pModel->setData(pModel->index(row,4),pLineEditSum->text());
    pModel->setData(pModel->index(row,5),pCbxCurrency->currentText());
    setWorkView();
    isEdit=false;
}

void Money_Repositary_Widget::deleteRecord(){
    pModel->removeRows(pTable->selectionModel()->currentIndex().row(),1);
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
    pLineEditDate->setText(pModel->data(pModel->index(row,0)).toString());
    pCbxType->setCurrentText(pModel->data(pModel->index(row,1)).toString());
    pCbxCategory->setCurrentText(pModel->data(pModel->index(row,2)).toString());
    pCbxDescription->setCurrentText(pModel->data(pModel->index(row,3)).toString());
    pLineEditSum->setText(pModel->data(pModel->index(row,4)).toString());
    pCbxCurrency->setCurrentText(pModel->data(pModel->index(row,5)).toString());
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
