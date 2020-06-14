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
    QObject::connect(pUserFileOperations,SIGNAL(nameAlreadyExists()),pWdgUser,SLOT(nameAlreadyExists()));
    QObject::connect(pWdgUser,SIGNAL(logIn(const QString,const QString)),pUserFileOperations,SLOT(checkPassword(const QString&,const QString&)));
}
