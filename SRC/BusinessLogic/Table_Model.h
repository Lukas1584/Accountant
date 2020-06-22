#pragma once
#include <QAbstractTableModel>
#include <QObject>
#include "SRC/DataBase/Data.h"

class Table_Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    Table_Model(Data* data, QObject *parent = 0);
    int rowCount(const QModelIndex&) const override ;
    int columnCount(const QModelIndex&) const override;
    QVariant data(const QModelIndex &index, int role= Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool insertRows(int row,int count=1, const QModelIndex& parent=QModelIndex()) override;
    bool removeRows(int row,int count=1, const QModelIndex& parent=QModelIndex()) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QStringList getCategories(const QString& type);
    QStringList getDescriptions(const QString& category);

signals:

private:
    Data *pData;
};
