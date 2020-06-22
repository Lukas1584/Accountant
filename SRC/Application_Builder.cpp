#include "Application_Builder.h"

Application_Builder::Application_Builder() : QObject()
{
    pData=new Data;

    pUserFileOperations=new User_File_Operations(pData);
    pModel=new Table_Model(pData);



    pWdgUser=new User_Widget(pUserFileOperations);
    pWdgMoneyRepositary=new Money_Repositary_Widget(pModel);
    pWdgReport= new Report_Widget(pModel);
    pWdgPlanning= new Planning_Widget;

    pMainWindow=new Main_Window(pWdgUser,pWdgMoneyRepositary,pWdgReport,pWdgPlanning);

    QObject::connect(pWdgUser,SIGNAL(disableMainWindow()),pMainWindow,SLOT(disableMainWindow()));
    QObject::connect(pWdgUser,SIGNAL(enableMainWindow()),pMainWindow,SLOT(enableMainWindow()));
    QObject::connect(pUserFileOperations,SIGNAL(dataIsLoaded()),pMainWindow,SLOT(dataIsLoaded()));
    QObject::connect(pUserFileOperations,SIGNAL(dataIsLoaded()),pWdgUser,SLOT(setWorkView()));
    QObject::connect(pUserFileOperations,SIGNAL(dataIsLoaded()),pWdgMoneyRepositary,SLOT(dataIsLoaded()));
    QObject::connect(pUserFileOperations,SIGNAL(wrongPassword()),pWdgUser,SLOT(wrongPassword()));
    QObject::connect(pWdgMoneyRepositary,SIGNAL(saveData()),pUserFileOperations,SLOT(saveData()));
    QObject::connect(pWdgUser,SIGNAL(exitUser()),pMainWindow,SLOT(exitUser()));
}

Application_Builder::~Application_Builder(){
    delete pMainWindow;
    delete pUserFileOperations;
    delete pProxyModel;
    delete pModel;
    delete pData;
}
