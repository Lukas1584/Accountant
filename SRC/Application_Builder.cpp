#include "Application_Builder.h"

Application_Builder::Application_Builder() : QObject()
{
    pData=new Data;

    pUserFileOperations=new User_File_Operations(pData);
    pDataOperations=new Data_Operations(pData);

    pWdgUser=new User_Widget(pUserFileOperations);
    pWdgMoneyRepositary=new Money_Repositary_Widget(pDataOperations);
    pWdgReport= new Report_Widget;
    pWdgPlanning= new Planning_Widget;

    pMainWindow=new Main_Window(pWdgUser,pWdgMoneyRepositary,pWdgReport,pWdgPlanning);

    QObject::connect(pWdgUser,SIGNAL(logIn(const QString,const QString)),pUserFileOperations,SLOT(checkPassword(const QString&,const QString&)));
    QObject::connect(pWdgUser,SIGNAL(disableMainWindow()),pMainWindow,SLOT(disableMainWindow()));
    QObject::connect(pWdgUser,SIGNAL(enableMainWindow()),pMainWindow,SLOT(enableMainWindow()));
    QObject::connect(pWdgUser,SIGNAL(addUser(const QString,const QString)),pUserFileOperations,SLOT(userCreation(const QString&,const QString&)));
    QObject::connect(pWdgUser,SIGNAL(addUser(const QString,const QString)),pMainWindow,SLOT(dataIsLoaded()));
    QObject::connect(pWdgUser,SIGNAL(addUser(QString,QString)),pMainWindow,SLOT(enabled(const QString&,const QString&)));
    QObject::connect(pWdgUser,SIGNAL(clearData()),pUserFileOperations,SLOT(clearData()));
    QObject::connect(pUserFileOperations,SIGNAL(dataIsLoaded()),pMainWindow,SLOT(dataIsLoaded()));
    QObject::connect(pUserFileOperations,SIGNAL(dataIsLoaded()),pWdgMoneyRepositary,SLOT(dataIsLoaded()));
    QObject::connect(pUserFileOperations,SIGNAL(dataIsLoaded()),pWdgUser,SLOT(setWorkView()));
    QObject::connect(pUserFileOperations,SIGNAL(wrongPassword()),pWdgUser,SLOT(wrongPassword()));
    QObject::connect(pUserFileOperations,SIGNAL(nameAlreadyExists()),pWdgUser,SLOT(nameAlreadyExists()));
    QObject::connect(pWdgMoneyRepositary,SIGNAL(saveData()),pUserFileOperations,SLOT(saveData()));




}
