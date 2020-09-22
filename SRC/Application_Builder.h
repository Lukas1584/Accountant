#pragma once
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/DataOperations.h"
#include "SRC/BusinessLogic/BusinessLogic.h"
#include "SRC/GUI/Main_Window.h"

class Application_Builder{    
public:
    Application_Builder();

private:
    std::shared_ptr<Data> pData;
    std::shared_ptr<DataFileOperations> pOperations;
    std::shared_ptr<BusinessLogic> pLogic;
    std::unique_ptr<Main_Window> pMainWindow;
};
