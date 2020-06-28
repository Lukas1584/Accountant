#include "Main_Window.h"

Main_Window::Main_Window(std::shared_ptr<QWidget> user, std::shared_ptr<QWidget> money, std::shared_ptr<QWidget> report, std::shared_ptr<QWidget> planning)
    : QWidget(),pWdgUser(user),pWdgMoney(money),pWdgReport(report),pWdgPlanning(planning)
{

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
    slotUserShow();

    QObject::connect(pBtnMoney,SIGNAL(clicked()),SLOT(slotMoneyShow()));
    QObject::connect(pBtnUser,SIGNAL(clicked()),SLOT(slotUserShow()));
    QObject::connect(pBtnReport,SIGNAL(clicked()),SLOT(slotReportShow()));
    QObject::connect(pBtnPlanning,SIGNAL(clicked()),SLOT(slotPlanningShow()));


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
    pHblMain->addWidget(&(*pWdgUser),5);
    pHblMain->addWidget(&(*pWdgMoney),5);
    pHblMain->addWidget(&(*pWdgReport),5);
    pHblMain->addWidget(&(*pWdgPlanning),5);
    setLayout(pHblMain);
    show();

}
void Main_Window::slotMoneyShow(){
    pWdgMoney->show();
    pWdgUser->hide();
    pWdgPlanning->hide();
    pWdgReport->hide();

}

void Main_Window::slotUserShow(){
    pWdgMoney->hide();
    pWdgUser->show();
    pWdgPlanning->hide();
    pWdgReport->hide();
}

void Main_Window::slotReportShow(){
    pWdgMoney->hide();
    pWdgUser->hide();
    pWdgPlanning->hide();
    pWdgReport->show();
}

void Main_Window::slotPlanningShow(){
    pWdgMoney->hide();
    pWdgUser->hide();
    pWdgPlanning->show();
    pWdgReport->hide();
}

void Main_Window::dataIsLoaded(){
    pBtnMoney->setEnabled(true);
    pBtnReport->setEnabled(true);
    pBtnPlanning->setEnabled(true);
    pLblBalance->show();
    slotMoneyShow();
}

void Main_Window::exitUser(){
    pBtnMoney->setEnabled(false);
    pBtnReport->setEnabled(false);
    pBtnPlanning->setEnabled(false);
    pLblBalance->hide();
    slotUserShow();
}

void Main_Window::disableMainWindow(){
    setEnabled(false);
}

void Main_Window::enableMainWindow(){
    setEnabled(true);
}


