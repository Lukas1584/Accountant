#pragma once
#include <QWidget>
#include <QTableWidget>
#include "SRC/BusinessLogic/Data_Operations.h"
#include <QtWidgets>

class Money_Repositary_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Money_Repositary_Widget(Data_Operations* d);
    bool eventFilter(QObject *pObject, QEvent *pEvent);

private slots:
    void save();
public slots:
    void dataIsLoaded();
signals:
    void saveData();

private:
    Data_Operations* pDataOperations;
    QTableWidget* pTable;
    QPushButton* pBtnSave;

};


