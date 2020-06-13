#pragma once
#include <QWidget>
#include <QTableWidget>
#include "SRC/BusinessLogic/Data_Operations.h"

class Money_Repositary_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Money_Repositary_Widget(Data_Operations* d);

signals:

private:
    Data_Operations* pDataOperations;
    QTableWidget* pTable;

};


