#pragma once
#include <QAbstractTableModel>
#include <QObject>
#include "SRC/DataBase/Data.h"

class Table_Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    Table_Model(Data* data, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    bool insertRows(int row,int count=1, const QModelIndex& parent=QModelIndex());
    bool removeRows(int row,int count=1, const QModelIndex& parent=QModelIndex());
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

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
