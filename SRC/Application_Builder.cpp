#include "Application_Builder.h"

Application_Builder::Application_Builder() : QObject()
{
    pData=new Data;

    pDataOperations=new Data_Operations(pData);

    pWdgUser=new User_Widget;
    pWdgMoneyRepositary=new Money_Repositary_Widget(pDataOperations);
    pWdgReport= new Report_Widget;
    pWdgPlanning= new Planning_Widget;



    pMainWindow=new Main_Window(pWdgUser,pWdgMoneyRepositary,pWdgReport,pWdgPlanning);
    pMainWindow->show();
}
