#pragma once
#include <QtWidgets>
#include <QObject>
#include "SRC/BusinessLogic/BusinessLogic.h"
#include <QPrintDialog>
#include <QPrinter>

class ReportWidget : public QWidget{
    Q_OBJECT
public:
    ReportWidget(std::shared_ptr<AbstractBusinessLogic> logic,QWidget* parent=nullptr);
    bool eventFilter(QObject*, QEvent*)override;
    void updateTable();
    void fillFields();

private slots:
    void filter();
    void fillComboBoxDescription();
    void fillComboBoxCategory();
    void categoryChecked(QStandardItem *item);
    void descriptionChecked(QStandardItem *item);
    void currencyChecked(QStandardItem *item);
    void resetFilter();
    void saveTxt();
    void savePDF();
    void print();

private:
    std::shared_ptr<AbstractBusinessLogic> pLogic;
    QTableWidget* pTable;

    QPushButton* pBtnSaveTxt;
    QPushButton* pBtnSavePDF;
    QPushButton* pBtnPrint;
    QPushButton* pBtnChart;
    QPushButton* pBtnReset;

    QDateEdit* pTimeEditTo;
    QDateEdit* pTimeEditFrom;
    QCheckBox *pChbxTypeProfit;
    QCheckBox *pChbxTypeLoss;
    QComboBox* pCbxCategory;
    QStandardItemModel* pModelCategory;
    QComboBox* pCbxDescription;
    QStandardItemModel* pModelDescription;
    QLineEdit* pLineEditSumFrom;
    QLineEdit* pLineEditSumTo;
    QComboBox* pCbxCurrency;
    QStandardItemModel* pModelCurrency;

    std::pair<bool,bool> typeToReport()const;
    std::vector<std::string> getComboBoxCheckedList(const QComboBox *combobox)const;
    void setTableDimensions();
    void setTableHeader();
    void fillDate();
    void fillSum();
    void fillComboBoxCurrency();
    void checkControl(QStandardItemModel* model,QStandardItem* item);
    void setCheckAll(QStandardItemModel* model,Qt::CheckState state);
    void fillComboBox(QStandardItemModel* model,std::list<std::string>& list);
};





