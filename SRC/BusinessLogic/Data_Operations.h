#pragma once
#include <QObject>
#include "SRC/DataBase/Data.h"


class Data_Operations : public QObject
{
    Q_OBJECT
public:
    explicit Data_Operations(Data* d);

signals:

private:
    Data* data;
};


