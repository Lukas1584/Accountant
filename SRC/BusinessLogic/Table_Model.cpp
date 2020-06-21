#include "Table_Model.h"

Table_Model::Table_Model(Data* data,QObject* parent) : QAbstractTableModel(parent),pData(data){}

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

bool Table_Model::insertRows(int row,int count, const QModelIndex& parent){
    if(parent.isValid()){
        return false;
    }
    beginInsertRows(QModelIndex(),row,row+count-1);
    pData->insertRows(row,count);
    endInsertRows();
    return true;
}

bool Table_Model::removeRows(int row,int count, const QModelIndex& parent){
    if(parent.isValid()){
        return false;
    }
    beginRemoveRows(QModelIndex(),row,row+count-1);
    pData->remove(row);
    endRemoveRows();
    return true;
}

bool Table_Model::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        pData->setData(index.row(),index.column(),value);
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

QStringList Table_Model::getCategories(const QString& type){
   return pData->getCategories(type);
}

QStringList Table_Model::getDescriptions(const QString& category){
    return pData->getDescriprions(category);
}
