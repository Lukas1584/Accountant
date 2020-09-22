#pragma once
#include <QtWidgets>
#include <QDate>
#include "SRC/BusinessLogic/Record_String.h"
#include "SRC/BusinessLogic/BusinessLogic.h"

class Money_Repositary_Widget : public QWidget{
    Q_OBJECT
public:
    Money_Repositary_Widget(std::shared_ptr<AbstractBusinessLogic> logic,QWidget* parent=nullptr);
    bool eventFilter(QObject*,QEvent* pEvent)override;

private slots:
    void addRecord();
    void deleteRecord();
    void editRecord();
    void cancelEditRecord();
    void categoryChanged();
    void dataIsLoaded();
    void saveData();
signals:
    void tableChanged();
private:
    std::shared_ptr<AbstractBusinessLogic> pLogic;
    QTableWidget* pTable;
    bool isEdit=false;

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
    void setEditView();
    void setWorkView();
    void setTableDimensions();
    void setTableHeader();
    QStringList convertToQList(const std::list<std::string>& list);
};


