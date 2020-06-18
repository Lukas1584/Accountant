#pragma once
#include <QWidget>
#include <QTableView>
#include "SRC/BusinessLogic/Table_Model.h"
#include <QtWidgets>
#include <QAbstractTableModel>

class Money_Repositary_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Money_Repositary_Widget(QAbstractTableModel* model);
    bool eventFilter(QObject *pObject, QEvent *pEvent);

private slots:
    void save();
    void addRecord();
public slots:

signals:
    void saveData();

private:
    QAbstractTableModel* pModel;
    QTableView* pTable;

    QPushButton* pBtnSave;
    QPushButton* pBtnAdd;
    QPushButton* pBtnEdit;
    QPushButton* pBtnDelete;


    QLineEdit* pLineEditDate;
    QComboBox* pCbxType;
    QComboBox* pCbxCategory;
    QComboBox* pCbxDescription;
    QLineEdit* pLineEditSum;
    QComboBox* pCbxCurrency;

};


