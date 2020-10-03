#pragma once
#include <QObject>
#include <QtWidgets>
#include "SRC/BusinessLogic/BusinessLogic.h"
#include "SRC/GUI/MoneyRepositaryWidget.h"
#include "SRC/GUI/ReportWidget.h"
#include "SRC/GUI/UserWidget.h"

class MainWindow : public QWidget{
    Q_OBJECT
public:
    MainWindow(std::shared_ptr<AbstractBusinessLogic> logic);

private slots:
    void moneyShow()const;
    void userShow()const;
    void reportShow();
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

    QLabel* pLblBalance;

    std::unique_ptr<MoneyRepositaryWidget> pWdgMoney;
    std::unique_ptr<ReportWidget> pWdgReport;
    std::unique_ptr<UserWidget> pWdgUser;

    void createWindows();
};

