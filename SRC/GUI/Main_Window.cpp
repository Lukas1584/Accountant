#include "Main_Window.h"

Main_Window::Main_Window(std::shared_ptr<AbstractBusinessLogic> logic):pLogic(logic){
    createWindows();

    resize(1200,800);
    pBtnUser=new  QPushButton(tr("Пользователь"));
    pBtnMoney=new QPushButton(tr("Кошелек"));
    pBtnMoney->setEnabled(false);
    pBtnReport=new QPushButton(tr("Отчет"));
    pBtnReport->setEnabled(false);
    pBtnPlanning=new QPushButton(tr("Планирование"));
    pBtnPlanning->setEnabled(false);
    pLblBalance = new QLabel(tr("Текущий баланс"));
    pLblBalance->hide();

    QVBoxLayout* pVblLeftMenu=new QVBoxLayout();
    pVblLeftMenu->setSpacing(20);
    pVblLeftMenu->setMargin(15);
    pVblLeftMenu->addWidget(pBtnUser);
    pVblLeftMenu->addWidget(pBtnMoney);
    pVblLeftMenu->addWidget(pBtnReport);
    pVblLeftMenu->addWidget(pBtnPlanning);
    pVblLeftMenu->addStretch(1);
    pVblLeftMenu->addWidget(pLblBalance,0);

    QHBoxLayout* pHblMain=new QHBoxLayout();
    pHblMain->addLayout(pVblLeftMenu,1);
    pHblMain->addWidget(pWdgUser.get(),5);
    pHblMain->addWidget(pWdgMoney.get(),5);
    pHblMain->addWidget(pWdgReport.get(),5);
    pHblMain->addWidget(pWdgPlanning.get(),5);
    setLayout(pHblMain);

    QObject::connect(pBtnMoney,SIGNAL(clicked()),SLOT(moneyShow()));
    QObject::connect(pBtnUser,SIGNAL(clicked()),SLOT(userShow()));
    QObject::connect(pBtnReport,SIGNAL(clicked()),SLOT(reportShow()));
    QObject::connect(pBtnPlanning,SIGNAL(clicked()),SLOT(planningShow()));

    QObject::connect(pWdgUser.get(),SIGNAL(disableMainWindow()),SLOT(disableMainWindow()));
    QObject::connect(pWdgUser.get(),SIGNAL(enableMainWindow()),SLOT(enableMainWindow()));
    QObject::connect(pWdgUser.get(),SIGNAL(dataIsLoaded()),SLOT(dataIsLoaded()));
    QObject::connect(pWdgUser.get(),SIGNAL(dataIsLoaded()),pWdgMoney.get(),SLOT(dataIsLoaded()));
    QObject::connect(pWdgUser.get(),SIGNAL(exitUser()),SLOT(exitUser()));
    QObject::connect(pWdgMoney.get(),SIGNAL(tableChanged()),SLOT(balance()));
    userShow();
    show();
}

void Main_Window::moneyShow() const{
    pWdgMoney->show();
    pWdgUser->hide();
    pWdgPlanning->hide();
    pWdgReport->hide();
}

void Main_Window::userShow() const{
    pWdgMoney->hide();
    pWdgUser->show();
    pWdgPlanning->hide();
    pWdgReport->hide();
}

void Main_Window::reportShow(){
    pWdgMoney->hide();
    pWdgUser->hide();
    pWdgPlanning->hide();
    pWdgReport->show();
    pLogic->updateReport();
    pWdgReport->fillFields();
    pWdgReport->updateTable();
}

void Main_Window::planningShow() const{
    pWdgMoney->hide();
    pWdgUser->hide();
    pWdgPlanning->show();
    pWdgReport->hide();
}

void Main_Window::dataIsLoaded() {
    pBtnMoney->setEnabled(true);
    pBtnReport->setEnabled(true);
    pBtnPlanning->setEnabled(true);
    balance();
    pLblBalance->show();
    moneyShow();
}

void Main_Window::exitUser() const{
    pBtnMoney->setEnabled(false);
    pBtnReport->setEnabled(false);
    pBtnPlanning->setEnabled(false);
    pLblBalance->hide();
    pLogic->clearData();
    userShow();
}

void Main_Window::disableMainWindow(){
    setEnabled(false);
}

void Main_Window::enableMainWindow(){
    setEnabled(true);
}

void Main_Window::balance(){
    QDate date=QDate::currentDate();
    pLblBalance->setText(pLogic->getBalance(date.toString("yyyy-MM-dd").toStdString()).c_str());
}

void Main_Window::createWindows(){
    pWdgUser=std::make_unique<User_Widget>(pLogic,this);
    pWdgMoney=std::make_unique<Money_Repositary_Widget>(pLogic,this);
    pWdgReport=std::make_unique<Report_Widget>(pLogic,this);
    pWdgPlanning=std::make_unique<Planning_Widget>(pLogic,this);
}
