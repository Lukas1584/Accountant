#include "Table_Model.h"

Table_Model::Table_Model(Data* data,QObject* parent) : QAbstractTableModel(parent),pData(data)
{

}

int Table_Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return pData->rows();
}

int Table_Model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return pData->columns();
}

QVariant Table_Model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return pData->at(index.column(),index.row());
    else return QVariant();
}

QVariant Table_Model::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
            return QVariant();
    if (orientation == Qt::Horizontal){
        switch (section){
        case 0:
            return tr("Дата");
        case 1:
            return tr("Тип");
        case 2:
            return tr("Категория");
        case 3:
            return tr("Описание");
        case 4:
            return tr("Сумма");
        case 5:
            return tr("Валюта");
        default:
            return QVariant();
        }
    }
    else return QVariant();
}
