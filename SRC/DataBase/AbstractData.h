#pragma once
#include <list>
#include <string>
#include "SRC/BusinessLogic/RecordString.h"

class AbstractData{
public:
    virtual unsigned int rows()const=0;
    virtual unsigned int columns()const=0;
    virtual void remove(const int row)=0;
    virtual void sort()=0;
    virtual const RecordString getRecord(const unsigned int row)const=0;
    virtual void setRecord(const unsigned int row,const RecordString& record)=0;
    virtual void clear()=0;
    virtual std::list<std::string> getAllCurrencies()const=0;
    virtual std::list<std::string> getAllTypes()const=0;
};


