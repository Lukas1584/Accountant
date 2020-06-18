#include "Data_Operations.h"
#include <vector>

Data_Operations::Data_Operations(Table_Model* model) : QObject(), pModel(model)
{

}

//QStringList Data_Operations::getData(){
//    std::vector<Record> tmp=pData->getData();
//    QStringList copyData;
//    for(auto i:tmp){
//        //copyData.push_back(QString(i.id));
//        copyData.push_back(QString(i.date.toString("dd.MM.yyyy")));
//        if(i.type==Record::LOSS){
//            copyData.push_back(tr("Убыток"));
//        }
//        else {
//            copyData.push_back(tr("Доход"));
//        }
//        copyData.push_back(i.category);
//        copyData.push_back(i.description);
//        copyData.push_back(QString::number(i.sum));
//        switch (i.currency){
//        case Record::USD:
//            copyData.push_back("USD");
//            break;
//        case Record::BYR:
//            copyData.push_back("BYR");
//            break;
//        case Record::RUB:
//            copyData.push_back("RUB");
//            break;
//        case Record::EUR:
//            copyData.push_back("EUR");
//            break;
//        }
//    }
//    return copyData;
//}

