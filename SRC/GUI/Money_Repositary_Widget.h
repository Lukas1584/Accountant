#pragma once
#include <QtWidgets>
//#include <QTableView>
//#include <QAbstractTableModel>
//#include <QHeaderView>
//#include <QEvent>
//#include <QVector>

class Money_Repositary_Widget : public QWidget
{
    Q_OBJECT
public:
    Money_Repositary_Widget(QAbstractTableModel* model);
    bool eventFilter(QObject *pObject, QEvent *pEvent);

private slots:
    void save();
    void addRecord();
    void deleteRecord();
    void editRecord();
    void cancelEditRecord();
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
    QPushButton* pBtnCnacel;

    QLineEdit* pLineEditDate;
    QComboBox* pCbxType;
    QComboBox* pCbxCategory;
    QComboBox* pCbxDescription;
    QLineEdit* pLineEditSum;
    QComboBox* pCbxCurrency;

    bool isEdit;

    void setEditView();
    void setWorkView();
};


