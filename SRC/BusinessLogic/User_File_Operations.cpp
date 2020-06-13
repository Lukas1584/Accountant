#include "User_File_Operations.h"

User_File_Operations::User_File_Operations(Data* d) : QObject(),pData(d)
{
    for(int i=0;i<10;i++){
        Record rec;
        rec.id=i;
        rec.date=QDate(QDate::currentDate());
        rec.category="Тестовая категория";
        rec.description="Тестовая запись";
        rec.sum=10*(i+1);
        rec.type=Record::PROFIT;
        rec.currency=Record::BYR;
        pData->add(rec);
    }
}





