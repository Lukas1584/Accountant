#pragma once
#include <QtWidgets>
#include <QObject>
#include <SRC/BusinessLogic/Report.h>

class Report_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Report_Widget(std::shared_ptr<Report> report);
    bool eventFilter(QObject*, QEvent*)override;
signals:

public slots:
    void updateTable();
    void fillFields();

private slots:
    void filter();
    void fillComboBoxDescription();
    void fillComboBoxCategory();

private:
    std::shared_ptr<Report> pReport;
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

    int typeToReport();
    std::vector<bool> currencyToReport()const;
    std::vector<std::string> getComboBoxCheckedList(const QComboBox *combobox)const;
    void setTableDimensions();
    void setTableHeader();
    void fillDate();
    void fillSum();
};





