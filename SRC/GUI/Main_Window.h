#pragma once
#include <QObject>
#include <QtWidgets>
#include "SRC/BusinessLogic/BusinessLogic.h"
#include "SRC/GUI/Money_Repositary_Widget.h"
#include "SRC/GUI/Planning_Widget.h"
#include "SRC/GUI/Report_Widget.h"
#include "SRC/GUI/User_Widget.h"

class Main_Window : public QWidget{
    Q_OBJECT
public:
    Main_Window(std::shared_ptr<AbstractBusinessLogic> logic);

private slots:
    void moneyShow()const;
    void userShow()const;
    void reportShow();
    void planningShow()const;
    void dataIsLoaded();
    void disableMainWindow();
    void enableMainWindow();
    void exitUser()const;
    void balance();

private:
    std::shared_ptr<AbstractBusinessLogic> pLogic;

    QPushButton* pBtnUser;
    QPushButton* pBtnMoney;
    QPushButton* pBtnReport;
    QPushButton* pBtnPlanning;

    QLabel* pLblBalance;

    std::unique_ptr<Money_Repositary_Widget> pWdgMoney;
    std::unique_ptr<Planning_Widget> pWdgPlanning;
    std::unique_ptr<Report_Widget> pWdgReport;
    std::unique_ptr<User_Widget> pWdgUser;

    void createWindows();
};

