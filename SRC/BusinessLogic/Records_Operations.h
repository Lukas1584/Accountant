#pragma once
#include <QObject>
#include "SRC/DataBase/Data.h"

class Records_Operations : public QObject
{
    Q_OBJECT
public:
    explicit Records_Operations(std::shared_ptr<Data> &data,QObject* pobj=0);

    int rowCount() const;
    int columnCount() const;
    Record_String data(const int row) const;
    void removeRow(const int row);
    void setData(const int row, const Record_String& rec);
    void sortData();
    std::list<std::string> getCategoryOrDescription(const std::string &typeOrCategory, const std::string &type)const;
    std::list<std::string> getCategory(const std::string &type)const;
    std::list<std::string> getDescription(const std::string& category)const;

signals:
    void dataChanged();

private:
    std::shared_ptr<Data> pData;
};











