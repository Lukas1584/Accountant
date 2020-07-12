#include "Application_Builder.h"

Application_Builder::Application_Builder() : QObject(){
    pData=std::make_shared<Data>();

    pUserFileOperations=new User_File_Operations(pData,this);
    pModel=new Records_Operations(pData,this);
    pReport=new Report(pData,this);
    pBalance=new Balance_Calculator(pData,this);

    pWdgUser=new User_Widget (pUserFileOperations);
    pWdgMoneyRepositary= new Money_Repositary_Widget(pModel);
    pWdgReport= new Report_Widget(pReport);
    pWdgPlanning=new Planning_Widget();

    pMainWindow= std::make_unique<Main_Window>(pWdgUser,pWdgMoneyRepositary,pWdgReport,pWdgPlanning,pBalance);

    QObject::connect(pWdgUser,SIGNAL(disableMainWindow()),pMainWindow.get(),SLOT(disableMainWindow()));
    QObject::connect(pWdgUser,SIGNAL(enableMainWindow()),pMainWindow.get(),SLOT(enableMainWindow()));
    QObject::connect(pUserFileOperations,SIGNAL(dataIsLoaded()),pMainWindow.get(),SLOT(dataIsLoaded()));
    QObject::connect(pUserFileOperations,SIGNAL(dataIsLoaded()),pWdgUser,SLOT(setWorkView()));
    QObject::connect(pUserFileOperations,SIGNAL(dataIsLoaded()),pWdgMoneyRepositary,SLOT(dataIsLoaded()));
    QObject::connect(pUserFileOperations,SIGNAL(wrongPassword()),pWdgUser,SLOT(wrongPassword()));
    QObject::connect(pWdgMoneyRepositary,SIGNAL(saveData()),pUserFileOperations,SLOT(saveData()));
    QObject::connect(pWdgUser,SIGNAL(exitUser()),pMainWindow.get(),SLOT(exitUser()));
    QObject::connect(pMainWindow.get(),SIGNAL(report()),pReport,SLOT(update()));
    QObject::connect(pMainWindow.get(),SIGNAL(report()),pWdgReport,SLOT(updateTable()));
    QObject::connect(pMainWindow.get(),SIGNAL(report()),pWdgReport,SLOT(fillFields()));
}
