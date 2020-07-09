#pragma once
#include <QtWidgets>
#include <QDate>
#include "SRC/BusinessLogic/Records_Operations.h"

class Money_Repositary_Widget : public QWidget
{
    Q_OBJECT
public:
    Money_Repositary_Widget(std::shared_ptr<Records_Operations>& model);
    bool eventFilter(QObject*,QEvent* pEvent)override;

private slots:
    void addRecord();
    void deleteRecord();
    void editRecord();
    void cancelEditRecord();
    void categoryChanged();

public slots:
    void dataIsLoaded();

signals:
    void saveData();

private:
    std::shared_ptr<Records_Operations> pModel;
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
    bool isEdit;
    void setEditView();
    void setWorkView();
    void setTableDimensions();
    void setTableHeader();
};


