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
        return QString::fromStdString(pData->at(index.row(),index.column()));
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

void Table_Model::sortData(){
    pData->sort();
}

QStringList Table_Model::getCategoryOrDescription(const QString& typeOrCategory,const QString& type) const{
    QStringList list;
    int keyColumn;
    int dependentColumn;
    if(type=="category"){
        keyColumn=1;
        dependentColumn=2;
    }
    if(type=="description"){
        keyColumn=2;
        dependentColumn=3;
    }
    for(int i=0;i<rowCount();i++){
        std::string categoryOrDescriptionCheck=pData->at(i,keyColumn);
        if(typeOrCategory.toStdString()==categoryOrDescriptionCheck){
            std::string categoryOrDescription=pData->at(i,dependentColumn);
            bool isUnique=true;
            for(auto j:list){
                if(j.toStdString()==categoryOrDescription)
                    isUnique=false;
            }
            if(isUnique)
                list.push_back(QString::fromStdString(categoryOrDescription));
        }
    }
    list.sort();
    return list;
}
