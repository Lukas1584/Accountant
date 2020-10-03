#include "ApplicationBuilder.h"

ApplicationBuilder::ApplicationBuilder(){

    pData=std::make_shared<Data>();
    pOperations=std::make_shared<DataFileOperations>(pData);

    pLogic=std::make_shared<BusinessLogic>(pData,pOperations);

    pMainWindow=std::make_unique<MainWindow>(pLogic);
}
