#pragma once
#include <QtWidgets>
#include <QDate>
#include "SRC/BusinessLogic/Records_Operations.h"
#include "SRC/BusinessLogic/Record_String.h"

class Money_Repositary_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Money_Repositary_Widget(Records_Operations *model,QWidget* parent=nullptr);
    bool eventFilter(QObject*,QEvent* pEvent)override;

private slots:
    void addRecord();
    void deleteRecord();
    void editRecord();
    void cancelEditRecord();
    void categoryChanged();
    void dataIsLoaded();

signals:
    void saveData();

private:
    Records_Operations* pModel;
    QTableWidget* pTable;

    QPushButton* pBtnSave;
    QPushButton* pBtnAdd;
    QPushButton* pBtnEdit;
    QPushButton* pBtnDelete;
    QPushButton* pBtnCnacel;

    QDateEdit* pTimeEdit;
    QComboBox* pCbxType;
    QComboBox* pCbxCategory;
    QComboBox* pCbxDescription;
    QLineEdit* pLineEditSum;
    QComboBox* pCbxCurrency;

    void updateTable();
    bool isEdit=false;
    void setEditView();
    void setWorkView();
    void setTableDimensions();
    void setTableHeader();
};


