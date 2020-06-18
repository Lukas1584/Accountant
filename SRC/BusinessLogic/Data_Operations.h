#pragma once
#include <QObject>
#include "SRC/BusinessLogic/Table_Model.h"
#include <QVector>


class Data_Operations : public QObject
{
    Q_OBJECT
public:
    Data_Operations(Table_Model* model);
//    QStringList getData();


signals:

private:
    Table_Model* pModel;
};


