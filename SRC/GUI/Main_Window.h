#pragma once
#include <QWidget>
#include <QtWidgets>
#include <SRC/GUI/User_Widget.h>
#include <SRC/GUI/Money_Repositary_Widget.h>
#include <SRC/GUI/Planning_Widget.h>
#include <SRC/GUI/Report_Widget.h>


class Main_Window : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Window(QWidget *parent = nullptr);

signals:

public slots:
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

    Money_Repositary_Widget* pWdgMoney=nullptr;
    Planning_Widget* pWdgPlanning=nullptr;
    Report_Widget* pWdgReport=nullptr;
    User_Widget* pWdgUser=nullptr;

    QWidget* pWdgCurrent;
    QHBoxLayout* pHblMain;

};


