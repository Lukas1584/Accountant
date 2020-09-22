#include "Application_Builder.h"

Application_Builder::Application_Builder(){

    pData=std::make_shared<Data>();
    pOperations=std::make_shared<DataFileOperations>(pData);

    pLogic=std::make_shared<BusinessLogic>(pData,pOperations);

    pMainWindow=std::make_unique<Main_Window>(pLogic);
}
