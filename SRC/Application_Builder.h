#pragma once
#include <QObject>

#include "SRC/GUI/Main_Window.h"
#include "SRC/GUI/Money_Repositary_Widget.h"
#include "SRC/GUI/Planning_Widget.h"
#include "SRC/GUI/Report_Widget.h"
#include "SRC/GUI/User_Widget.h"


#include "SRC/DataBase/Data.h"



class Application_Builder : public QObject
{
    Q_OBJECT
public:
    explicit Application_Builder();

signals:


private:

    Data* pData;

    User_Widget* pWdgUser;
    Money_Repositary_Widget* pWdgMoneyRepositary;
    Report_Widget* pWdgReport;
    Planning_Widget* pWdgPlanning;

    Main_Window* pMainWindow;

};


