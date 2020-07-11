#pragma once
#include <QtWidgets>
#include <QObject>
#include <SRC/BusinessLogic/Report.h>

class Report_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Report_Widget(Report* report,QWidget* parent=nullptr);
    bool eventFilter(QObject*, QEvent*)override;
signals:

private slots:
    void updateTable();
    void fillFields();
    void filter();
    void fillComboBoxDescription();
    void fillComboBoxCategory();
    void categoryChecked(QStandardItem *item);
    void descriptionChecked(QStandardItem *item);
    void resetFilter();

private:
    Report* pReport;
    QTableWidget* pTable;

    QPushButton* pBtnSaveTxt;
    QPushButton* pBtnSaveExcel;
    QPushButton* pBtnPrint;
    QPushButton* pBtnChart;
    QPushButton* pBtnApply;
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
    QCheckBox *pChbxUsd;
    QCheckBox *pChbxByr;
    QCheckBox *pChbxRub;
    QCheckBox *pChbxEur;

    int typeToReport()const;
    std::vector<bool> currencyToReport()const;
    std::vector<std::string> getComboBoxCheckedList(const QComboBox *combobox)const;
    void setTableDimensions();
    void setTableHeader();
    void fillDate();
    void fillSum();
    void checkControl(QStandardItemModel* model,QStandardItem* item);
    void setCheckAll(QStandardItemModel* model,Qt::CheckState state);
};





