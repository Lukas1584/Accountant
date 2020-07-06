#include "Application_Builder.h"

Application_Builder::Application_Builder() : QObject()
{
    pData=std::make_shared<Data>();

    pUserFileOperations=std::make_shared<User_File_Operations>(pData);
    pModel=std::make_shared<Table_Model>(pData);
    pReport=std::make_shared<Report>(pData);

    pWdgUser=std::make_shared<User_Widget>(pUserFileOperations);
    pWdgMoneyRepositary=std::make_shared<Money_Repositary_Widget>(pModel);
    pWdgReport= std::make_shared<Report_Widget>(pReport);
    pWdgPlanning=std::make_shared<Planning_Widget>();

    pMainWindow= std::make_unique<Main_Window>(pWdgUser,pWdgMoneyRepositary,pWdgReport,pWdgPlanning);

    QObject::connect(pWdgUser.get(),SIGNAL(disableMainWindow()),pMainWindow.get(),SLOT(disableMainWindow()));
    QObject::connect(pWdgUser.get(),SIGNAL(enableMainWindow()),pMainWindow.get(),SLOT(enableMainWindow()));
    QObject::connect(pUserFileOperations.get(),SIGNAL(dataIsLoaded()),pMainWindow.get(),SLOT(dataIsLoaded()));
    QObject::connect(pUserFileOperations.get(),SIGNAL(dataIsLoaded()),pWdgUser.get(),SLOT(setWorkView()));
    QObject::connect(pUserFileOperations.get(),SIGNAL(dataIsLoaded()),pWdgMoneyRepositary.get(),SLOT(dataIsLoaded()));
    QObject::connect(pUserFileOperations.get(),SIGNAL(wrongPassword()),pWdgUser.get(),SLOT(wrongPassword()));
    QObject::connect(pWdgMoneyRepositary.get(),SIGNAL(saveData()),pUserFileOperations.get(),SLOT(saveData()));
    QObject::connect(pWdgUser.get(),SIGNAL(exitUser()),pMainWindow.get(),SLOT(exitUser()));

    QObject::connect(pMainWindow.get(),SIGNAL(report()),pReport.get(),SLOT(update()));
    QObject::connect(pMainWindow.get(),SIGNAL(report()),pWdgReport.get(),SLOT(updateTable()));



}
