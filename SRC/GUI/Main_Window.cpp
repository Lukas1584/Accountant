#include "Main_Window.h"
#include <QObject>

Main_Window::Main_Window(QWidget *parent) : QWidget(parent)
{

    resize(1200,800);
    pBtnUser=new  QPushButton(tr("Пользователь"));
    pBtnMoney=new QPushButton(tr("Кошелек"));
    pBtnReport=new QPushButton(tr("Отчет"));
    pBtnPlanning=new QPushButton(tr("Планирование"));

    pLblBalance = new QLabel(tr("Текущий баланс"));

    pWdgPlanning=new Planning_Widget();
    pWdgUser=new User_Widget();
    pWdgMoney=new Money_Repositary_Widget();
    pWdgReport=new Report_Widget();
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

    pHblMain=new QHBoxLayout();
    pHblMain->addLayout(pVblLeftMenu,1);
    pHblMain->addWidget(pWdgUser,5);
    pHblMain->addWidget(pWdgMoney,5);
    pHblMain->addWidget(pWdgReport,5);
    pHblMain->addWidget(pWdgPlanning,5);
    setLayout(pHblMain);

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
