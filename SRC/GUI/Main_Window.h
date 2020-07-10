#pragma once
#include <QtWidgets>

class Main_Window : public QWidget
{
    Q_OBJECT
public:
    Main_Window(QWidget *user,
                QWidget* money,
                QWidget* report,
                QWidget* planning,
                QWidget *parent=nullptr);

signals:
    void report();

private slots:
    void dataIsLoaded()const;
    void disableMainWindow();
    void enableMainWindow();
    void exitUser()const;
    void slotMoneyShow()const;
    void slotUserShow()const;
    void slotReportShow();
    void slotPlanningShow()const;

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

