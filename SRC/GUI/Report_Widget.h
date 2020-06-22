#pragma once
#include <QtWidgets>
#include "SRC/BusinessLogic/Table_Model.h"


class Report_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Report_Widget(Table_Model* model);

signals:


private:
    Table_Model* pModel;
    QTableView* pTable;

    QPushButton* pBtnSave;
    QPushButton* pBtnAdd;
    QPushButton* pBtnEdit;
    QPushButton* pBtnDelete;
    QPushButton* pBtnCnacel;

    QDateTimeEdit* pTimeEdit;
    QComboBox* pCbxType;
    QComboBox* pCbxCategory;
    QComboBox* pCbxDescription;
    QLineEdit* pLineEditSum;
    QComboBox* pCbxCurrency;

    bool isEdit;

    void setEditView();
    void setWorkView();

};

