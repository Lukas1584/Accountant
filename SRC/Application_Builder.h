#pragma once
#include <QObject>

#include "SRC/GUI/Main_Window.h"
#include "SRC/GUI/Money_Repositary_Widget.h"
#include "SRC/GUI/Planning_Widget.h"
#include "SRC/GUI/Report_Widget.h"
#include "SRC/GUI/User_Widget.h"

#include "SRC/BusinessLogic/User_File_Operations.h"
#include "SRC/BusinessLogic/Table_Model.h"
#include "SRC/BusinessLogic/Report.h"

#include "SRC/DataBase/Data.h"


class Application_Builder : public QObject
{
    Q_OBJECT
public:
    explicit Application_Builder();

signals:

private:
    std::shared_ptr<Data> pData;

    std::shared_ptr<User_File_Operations> pUserFileOperations;
    std::shared_ptr<Table_Model> pModel;
    std::shared_ptr<Report> pReport;

    std::shared_ptr<User_Widget> pWdgUser;
    std::shared_ptr<Money_Repositary_Widget> pWdgMoneyRepositary;
    std::shared_ptr<Report_Widget> pWdgReport;
    std::shared_ptr<Planning_Widget> pWdgPlanning;

    std::unique_ptr<Main_Window> pMainWindow;
};
