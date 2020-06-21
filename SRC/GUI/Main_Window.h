#pragma once
#include <QtWidgets>
//#include <QObject>

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
    void exitUser();

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


