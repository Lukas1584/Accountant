#pragma once
#include "SRC/DataBase/Data.h"
#include "SRC/DataBase/DataOperations.h"
#include "SRC/BusinessLogic/BusinessLogic.h"
#include "SRC/GUI/MainWindow.h"

class ApplicationBuilder{
public:
    ApplicationBuilder();

private:
    std::shared_ptr<Data> pData;
    std::shared_ptr<DataFileOperations> pOperations;
    std::shared_ptr<BusinessLogic> pLogic;
    std::unique_ptr<MainWindow> pMainWindow;
};
