#include "Table_Model.h"

Table_Model::Table_Model(std::shared_ptr<Data>& data,QObject* parent) : QAbstractTableModel(parent),pData(data){}

int Table_Model::rowCount(const QModelIndex&) const{
    return pData->rows();
}

int Table_Model::columnCount(const QModelIndex&) const{
    return pData->columns();
}

QVariant Table_Model::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole){
        return QString::fromStdString(pData->at(index.column(),index.row()));
    }
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

bool Table_Model::setData(const QModelIndex& index, const QVariant& value, int role){
    if (index.isValid() && role == Qt::EditRole)
    {
        pData->setData(index.row(),index.column(),value.toString().toStdString());
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

QStringList Table_Model::getCategories(const QString& type){
   std::list<std::string> cat=pData->getCategories(type.toStdString());
   QStringList categories;
   for (auto i:cat){
       categories.push_back(QString::fromStdString(i));
   }
   return categories;
}

QStringList Table_Model::getDescriptions(const QString& category){
    std::list<std::string> des=pData->getDescriprions(category.toStdString());
    QStringList descriptions;
    for (auto i:des){
        descriptions.push_back(QString::fromStdString(i));
    }
    return descriptions;
}

