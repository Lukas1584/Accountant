#include "Password_Widget.h"

Password_Widget::Password_Widget(QWidget *parent) : QWidget(parent)
{
    resize(400,150);

    pBtnOK=new QPushButton(tr("Ок"));
    pBtnCancel=new QPushButton(tr("Отмена"));

    pLeName= new QLineEdit;
    pLePassword=new QLineEdit;
    pLePassword->setEchoMode(QLineEdit::Password);
    pLePasswordConfirmation=new QLineEdit;
    pLePasswordConfirmation->setEchoMode(QLineEdit::Password);

    QLabel* pLblName=new QLabel(tr("Имя"));
    QLabel* pLblPassword=new QLabel(tr("Пароль"));
    QLabel* pLblPasswordConfirmation=new QLabel(tr("Подтверждение пароля"));

    QObject::connect(pBtnOK,SIGNAL(clicked()),this,SLOT(slotClickedOk()));
    QObject::connect(pBtnCancel,SIGNAL(clicked()),this,SLOT(slotClickedCancel()));

    QGridLayout* pGrdMain=new QGridLayout;
    pGrdMain->addWidget(pLblName,0,0,Qt::AlignRight);
    pGrdMain->addWidget(pLblPassword,1,0,Qt::AlignRight);
    pGrdMain->addWidget(pLblPasswordConfirmation,2,0,Qt::AlignRight);
    pGrdMain->addWidget(pLeName,0,1);
    pGrdMain->addWidget(pLePassword,1,1);
    pGrdMain->addWidget(pLePasswordConfirmation,2,1);
    pGrdMain->addWidget(pBtnOK,0,2);
    pGrdMain->addWidget(pBtnCancel,1,2);

    setLayout(pGrdMain);
}
void Password_Widget::slotClickedOk(){
    if(pLePassword->text()!=pLePasswordConfirmation->text()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this,tr("Сообщение"),tr("Пароли не совпадают!"));
        return;
    }
    //Задать рег выражение для логина
    if(pLeName->text()==""||pLeName->text()==" "){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this,tr("Сообщение"),tr("Вы забыли указать имя!"));
        return;
    }
    emit clickedOk(pLeName->text(),pLePassword->text());
}

void Password_Widget::slotClickedCancel(){
   this->destroy();
}
