#pragma once
#include <QObject>
#include "SRC/DataBase/Data.h"

class Records_Operations : public QObject
{
    Q_OBJECT
public:
    explicit Records_Operations(std::shared_ptr<Data> &data);

    int rowCount() const;
    int columnCount() const;
    std::string data(const int row, const int column) const;
    void insertRows(int row,int count=1);
    void removeRows(int row);
    void setData(const int row, const int column, const std::string& value);
    void sortData();
    std::list<std::string> getCategoryOrDescription(const std::string &typeOrCategory, const std::string &type)const;

signals:
    void dataChanged();

private:
    std::shared_ptr<Data> pData;
};











