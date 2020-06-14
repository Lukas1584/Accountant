#pragma once
#include <QWidget>
#include <QtWidgets>
#include "SRC/GUI/User_Widget.h"
#include "SRC/GUI/Money_Repositary_Widget.h"
#include "SRC/GUI/Planning_Widget.h"
#include "SRC/GUI/Report_Widget.h"



class Main_Window : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Window(User_Widget* User,Money_Repositary_Widget* Money,Report_Widget* Report,Planning_Widget* Planning);

signals:

public slots:
    void slotMoneyShow();
    void slotUserShow();
    void slotReportShow();
    void slotPlanningShow();
 //   void enabled(QString,QString);

private:
    QPushButton* pBtnUser;
    QPushButton* pBtnMoney;
    QPushButton* pBtnReport;
    QPushButton* pBtnPlanning;

    QLabel* pLblBalance;

    User_Widget* pWdgUser;
    Money_Repositary_Widget* pWdgMoney;
    Report_Widget* pWdgReport;
    Planning_Widget* pWdgPlanning;
};


