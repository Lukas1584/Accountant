#pragma once
#include <QObject>
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/Record.h"
#include <QVector>


class Data_Operations : public QObject
{
    Q_OBJECT
public:
    explicit Data_Operations(Data* d);
    QStringList getData();

signals:

private:
    Data* pData;
};


