#pragma once
#include <list>
#include "SRC/BusinessLogic/Record_String.h"

class AbstractData{
public:
    virtual int rows()const=0;
    virtual int columns()const=0;
    virtual void remove(const int row)=0;
    virtual void sort()=0;
    virtual const Record_String getRecord(const int row)=0;
    virtual void setRecord(const int row,const Record_String& record)=0;
    virtual void clear()=0;
    virtual std::list<std::string> getAllCurrencies()=0;
    virtual std::list<std::string> getAllTypes()=0;
};
