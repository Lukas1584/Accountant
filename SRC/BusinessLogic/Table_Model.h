#pragma once
#include <QAbstractTableModel>
#include <QObject>
#include "SRC/DataBase/Data.h"

class Table_Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    Table_Model(Data* data);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

signals:

private:
    Data *pData;
};


/*

virtual bool
dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override

virtual Qt::ItemFlags
flags(const QModelIndex &index) const override

virtual QModelIndex
index(int row, int column, const QModelIndex &parent = QModelIndex()) const override

virtual QModelIndex
sibling(int row, int column, const QModelIndex &idx) const override


*/
