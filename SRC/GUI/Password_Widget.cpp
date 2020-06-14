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
    QObject::connect(pBtnCancel,SIGNAL(clicked()),this,SLOT(clickedCancel()));

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
    QString login;
    QString password;
    if(pLePassword->text()!=pLePasswordConfirmation->text()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this,tr("Сообщение"),tr("Пароли не совпадают!"));
        return;
    }
    login=pLeName->text();
    password=pLePassword->text();
    emit clickedOk(login,password);
}

void Password_Widget::clickedCancel(){
   this->destroy();
}
