#pragma once
#include <QtWidgets>
#include "SRC/BusinessLogic/Balance_Calculator.h"

class Main_Window : public QWidget
{
    Q_OBJECT
public:
    Main_Window(QWidget *user,
                QWidget* money,
                QWidget* report,
                QWidget* planning,
                Balance_Calculator* balance,
                QWidget *parent=nullptr);

signals:
    void report();

private slots:
    void dataIsLoaded();
    void disableMainWindow();
    void enableMainWindow();
    void exitUser()const;
    void slotMoneyShow()const;
    void slotUserShow()const;
    void slotReportShow();
    void slotPlanningShow()const;
    void balance();

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
    Balance_Calculator* pBalance;
};

