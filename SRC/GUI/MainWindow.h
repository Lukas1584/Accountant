#pragma once
#include <QtWidgets>
#include <memory>
#include <QDate>
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
    void exitUser()const;
    void balance();

private:
    std::shared_ptr<AbstractBusinessLogic> pLogic;

    QPushButton* pBtnUser;
    QPushButton* pBtnMoney;
    QPushButton* pBtnReport;

    QLabel* pLblBalance;

    MoneyRepositaryWidget* pWdgMoney;
    ReportWidget* pWdgReport;
    UserWidget* pWdgUser;

    void createWindows();
    void drawMainWindow();
    void connectWindows();
};

