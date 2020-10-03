#pragma once
#include <list>
#include "SRC/BusinessLogic/RecordString.h"

class AbstractData{
public:
    virtual int rows()const=0;
    virtual int columns()const=0;
    virtual void remove(const int row)=0;
    virtual void sort()=0;
    virtual const RecordString getRecord(const int row)const=0;
    virtual void setRecord(const int row,const RecordString& record)=0;
    virtual void clear()=0;
    virtual std::list<std::string> getAllCurrencies()const=0;
    virtual std::list<std::string> getAllTypes()const=0;
};
