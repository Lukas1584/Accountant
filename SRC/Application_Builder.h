#pragma once
#include <QObject>

#include "SRC/GUI/Main_Window.h"
#include "SRC/GUI/Money_Repositary_Widget.h"
#include "SRC/GUI/Planning_Widget.h"
#include "SRC/GUI/Report_Widget.h"
#include "SRC/GUI/User_Widget.h"

#include "SRC/BusinessLogic/User_File_Operations.h"
#include "SRC/BusinessLogic/Report.h"
#include "SRC/BusinessLogic/Records_Operations.h"
#include "SRC/BusinessLogic/Balance_Calculator.h"

#include "SRC/DataBase/Data.h"


class Application_Builder : public QObject
{
    Q_OBJECT
public:
    explicit Application_Builder();

private:
    std::shared_ptr<Data> pData;

    User_File_Operations* pUserFileOperations;
    Records_Operations* pModel;
    Report* pReport;
    Balance_Calculator* pBalance;

    User_Widget* pWdgUser;
    Money_Repositary_Widget* pWdgMoneyRepositary;
    Report_Widget* pWdgReport;
    Planning_Widget* pWdgPlanning;

    std::unique_ptr<Main_Window> pMainWindow;
};
