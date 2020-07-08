#pragma once
#include <QtWidgets>
#include <SRC/BusinessLogic/Table_Model.h>

class Money_Repositary_Widget : public QWidget
{
    Q_OBJECT
public:
    Money_Repositary_Widget(std::shared_ptr<Table_Model>& model);
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
    std::shared_ptr<Table_Model> pModel;
    QTableView* pTable;

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

    bool isEdit;

    void setEditView();
    void setWorkView();
};


