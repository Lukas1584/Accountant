#include "Change_Password_Widget.h"

Change_Password_Widget::Change_Password_Widget(QWidget *parent) : QWidget(parent)
{
    resize(400,150);

    pBtnOK=new QPushButton(tr("Ок"));
    pBtnCancel=new QPushButton(tr("Отмена"));

    pLeOldPassword= new QLineEdit;
    pLeOldPassword->setEchoMode(QLineEdit::Password);
    pLePassword=new QLineEdit;
    pLePassword->setEchoMode(QLineEdit::Password);
    pLePasswordConfirmation=new QLineEdit;
    pLePasswordConfirmation->setEchoMode(QLineEdit::Password);

    QLabel* pLblName=new QLabel(tr("Текущий пароль"));
    QLabel* pLblPassword=new QLabel(tr("Новый пароль"));
    QLabel* pLblPasswordConfirmation=new QLabel(tr("Подтверждение пароля"));

    QObject::connect(pBtnOK,SIGNAL(clicked()),this,SLOT(slotClickedOk()));
    QObject::connect(pBtnCancel,SIGNAL(clicked()),this,SLOT(slotClickedCancel()));

    QGridLayout* pGrdMain=new QGridLayout;
    pGrdMain->addWidget(pLblName,0,0,Qt::AlignRight);
    pGrdMain->addWidget(pLblPassword,1,0,Qt::AlignRight);
    pGrdMain->addWidget(pLblPasswordConfirmation,2,0,Qt::AlignRight);
    pGrdMain->addWidget(pLeOldPassword,0,1);
    pGrdMain->addWidget(pLePassword,1,1);
    pGrdMain->addWidget(pLePasswordConfirmation,2,1);
    pGrdMain->addWidget(pBtnOK,0,2);
    pGrdMain->addWidget(pBtnCancel,1,2);

    setLayout(pGrdMain);
}
void Change_Password_Widget::slotClickedOk(){
    if(pLePassword->text()!=pLePasswordConfirmation->text()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this,tr("Сообщение"),tr("Пароли не совпадают!"));
        Q_UNUSED(reply);
        return;
    }
    emit clickedOk(pLeOldPassword->text(),pLePassword->text());
}

void Change_Password_Widget::slotClickedCancel(){
    emit clickedCancel();
    this->destroy();
}
