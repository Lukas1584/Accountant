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
    Main_Window(QWidget* User,QWidget* Money,QWidget* Report,QWidget* Planning);

signals:

public slots:
    void dataIsLoaded();
    void disableMainWindow();
    void enableMainWindow();

private slots:
    void slotMoneyShow();
    void slotUserShow();
    void slotReportShow();
    void slotPlanningShow();

private:
    QPushButton* pBtnUser;
    QPushButton* pBtnMoney;
    QPushButton* pBtnReport;
    QPushButton* pBtnPlanning;

    QLabel* pLblBalance;

    QWidget* pWdgUser;
    QWidget* pWdgMoney;
    QWidget* pWdgReport;
    QWidget* pWdgPlanning;
};


