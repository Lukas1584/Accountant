#pragma once
#include <QObject>
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/Record.h"

class User_File_Operations : public QObject
{
    Q_OBJECT
public:
    explicit User_File_Operations(Data* d);

signals:


private:
    Data* pData;
};


