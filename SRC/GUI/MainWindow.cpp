#include "MainWindow.h"

MainWindow::MainWindow(std::shared_ptr<AbstractBusinessLogic> logic):pLogic(logic){
    createWindows();
    drawMainWindow();
    connectWindows();
    userShow();
    show();
}

void MainWindow::createWindows(){
    pWdgUser=new UserWidget(pLogic,this);
    pWdgMoney=new MoneyRepositaryWidget(pLogic,this);
    pWdgReport=new ReportWidget(pLogic,this);
}

void MainWindow::drawMainWindow(){
    resize(1200,800);
    pBtnUser=new  QPushButton(tr("Пользователь"));
    pBtnMoney=new QPushButton(tr("Кошелек"));
    pBtnMoney->setEnabled(false);
    pBtnReport=new QPushButton(tr("Отчет"));
    pBtnReport->setEnabled(false);
    pLblBalance = new QLabel(tr("Текущий баланс"));
    pLblBalance->hide();

    QVBoxLayout* pVblLeftMenu=new QVBoxLayout();
    pVblLeftMenu->setSpacing(20);
    //pVblLeftMenu->setMargin(15);

    pVblLeftMenu->addWidget(pBtnUser);
    pVblLeftMenu->addWidget(pBtnMoney);
    pVblLeftMenu->addWidget(pBtnReport);
    pVblLeftMenu->addStretch(1);
    pVblLeftMenu->addWidget(pLblBalance,0);

    QHBoxLayout* pHblMain=new QHBoxLayout();
    pHblMain->addLayout(pVblLeftMenu,1);
    pHblMain->addWidget(pWdgUser,5);
    pHblMain->addWidget(pWdgMoney,5);
    pHblMain->addWidget(pWdgReport,5);
    setLayout(pHblMain);
}

void MainWindow::connectWindows(){
    QObject::connect(pBtnMoney,SIGNAL(clicked()),SLOT(moneyShow()));
    QObject::connect(pBtnUser,SIGNAL(clicked()),SLOT(userShow()));
    QObject::connect(pBtnReport,SIGNAL(clicked()),SLOT(reportShow()));

    QObject::connect(pWdgUser,SIGNAL(dataIsLoaded()),SLOT(dataIsLoaded()));
    QObject::connect(pWdgUser,SIGNAL(dataIsLoaded()),pWdgMoney,SLOT(dataIsLoaded()));
    QObject::connect(pWdgUser,SIGNAL(exitUser()),SLOT(exitUser()));
    QObject::connect(pWdgMoney,SIGNAL(tableChanged()),SLOT(balance()));
}

void MainWindow::moneyShow() const{
    pWdgMoney->show();
    pWdgUser->hide();
    pWdgReport->hide();
}

void MainWindow::userShow() const{
    pWdgMoney->hide();
    pWdgUser->show();
    pWdgReport->hide();
}

void MainWindow::reportShow(){
    pWdgMoney->hide();
    pWdgUser->hide();
    pWdgReport->show();
    pLogic->updateReport();
    pWdgReport->fillFields();
    pWdgReport->updateTable();
}

void MainWindow::dataIsLoaded() {
    pBtnMoney->setEnabled(true);
    pBtnReport->setEnabled(true);
    balance();
    moneyShow();
}

void MainWindow::exitUser() const{
    pBtnMoney->setEnabled(false);
    pBtnReport->setEnabled(false);
    pLblBalance->hide();
    pLogic->clearData();
    userShow();
}

void MainWindow::balance(){
    pLblBalance->setText(pLogic->getBalance(QDate::currentDate().toString("yyyy-MM-dd").toStdString()).c_str());
    pLblBalance->show();
}
