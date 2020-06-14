#include "Main_Window.h"
#include <QObject>

Main_Window::Main_Window(User_Widget* User,Money_Repositary_Widget* Money,Report_Widget* Report,Planning_Widget* Planning)
    : QWidget(), pWdgUser(User), pWdgMoney(Money), pWdgReport(Report),pWdgPlanning(Planning)
{

    resize(1200,800);
    pBtnUser=new  QPushButton(tr("Пользователь"));
    pBtnMoney=new QPushButton(tr("Кошелек"));
    pBtnReport=new QPushButton(tr("Отчет"));
    pBtnPlanning=new QPushButton(tr("Планирование"));

    pLblBalance = new QLabel(tr("Текущий баланс"));

    slotUserShow();

    QObject::connect(pBtnMoney,SIGNAL(clicked()),SLOT(slotMoneyShow()));
    QObject::connect(pBtnUser,SIGNAL(clicked()),SLOT(slotUserShow()));
    QObject::connect(pBtnReport,SIGNAL(clicked()),SLOT(slotReportShow()));
    QObject::connect(pBtnPlanning,SIGNAL(clicked()),SLOT(slotPlanningShow()));
    //QObject::connect(pWdgUser,SIGNAL(addUser(QString,QString)),this,SLOT(enabled()));


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
    pHblMain->addWidget(pWdgUser,5);
    pHblMain->addWidget(pWdgMoney,5);
    pHblMain->addWidget(pWdgReport,5);
    pHblMain->addWidget(pWdgPlanning,5);
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
//void Main_Window::enabled(QString,QString){
//    this->setEnabled(false);
//}
