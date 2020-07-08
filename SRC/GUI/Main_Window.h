#pragma once
#include <QtWidgets>

class Main_Window : public QWidget
{
    Q_OBJECT
public:
    Main_Window(std::shared_ptr<QWidget> user, std::shared_ptr<QWidget> money, std::shared_ptr<QWidget> report, std::shared_ptr<QWidget> planning);

signals:
    void report();

public slots:
    void dataIsLoaded()const;
    void disableMainWindow();
    void enableMainWindow();
    void exitUser()const;

private slots:
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

    std::shared_ptr<QWidget> pWdgUser;
    std::shared_ptr<QWidget> pWdgMoney;
    std::shared_ptr<QWidget> pWdgReport;
    std::shared_ptr<QWidget> pWdgPlanning;
};

