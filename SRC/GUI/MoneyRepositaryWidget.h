#pragma once
#include <QtWidgets>
#include <QDate>
#include <vector>
#include <memory>
#include <string>
#include <QStringList>
#include "SRC/BusinessLogic/RecordString.h"
#include "SRC/BusinessLogic/BusinessLogic.h"

class MoneyRepositaryWidget : public QWidget{
    Q_OBJECT
public:
    MoneyRepositaryWidget(std::shared_ptr<AbstractBusinessLogic> logic,QWidget* parent);
    bool eventFilter(QObject*,QEvent* pEvent)override;

private slots:
    void addRecord();
    void deleteRecord();
    void editRecord();
    void cancelEditRecord();
    void categoryChanged();
    void dataIsLoaded();
    void saveData();
    void updateCbxCategory();
signals:
    void tableChanged();
private:
    std::shared_ptr<AbstractBusinessLogic> pLogic;
    bool isEdit=false;

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

    void drawWindow();
    void connectButtons();
    void updateTable();
    void setEditView();
    void setWorkView();
    void setTableDimensions();
    void setTableHeader();
    QStringList convertToQList(const std::list<std::string>& list)const;
};


