#include "PasswordWidget.h"

PasswordWidget::PasswordWidget(){
    drawWindow();
    QObject::connect(pBtnOK,SIGNAL(clicked()),SLOT(slotClickedOk()));
    setModal(true);
}

void PasswordWidget::drawWindow(){
    resize(400,150);

    pBtnOK=new QPushButton(tr("Ок"));

    pLeName= new QLineEdit;
    pLePassword=new QLineEdit;
    pLePassword->setEchoMode(QLineEdit::Password);
    pLePasswordConfirmation=new QLineEdit;
    pLePasswordConfirmation->setEchoMode(QLineEdit::Password);

    QLabel* pLblName=new QLabel(tr("Имя"));
    QLabel* pLblPassword=new QLabel(tr("Пароль"));
    QLabel* pLblPasswordConfirmation=new QLabel(tr("Подтверждение пароля"));
    QGridLayout* pGrdMain=new QGridLayout;
    pGrdMain->addWidget(pLblName,0,0,Qt::AlignRight);
    pGrdMain->addWidget(pLblPassword,1,0,Qt::AlignRight);
    pGrdMain->addWidget(pLblPasswordConfirmation,2,0,Qt::AlignRight);
    pGrdMain->addWidget(pLeName,0,1);
    pGrdMain->addWidget(pLePassword,1,1);
    pGrdMain->addWidget(pLePasswordConfirmation,2,1);
    pGrdMain->addWidget(pBtnOK,0,2);
    setLayout(pGrdMain);
}

void PasswordWidget::slotClickedOk(){
    if(pLePassword->text()!=pLePasswordConfirmation->text()){
        QMessageBox::information(this,tr("Сообщение"),tr("Пароли не совпадают!"));
        return;
    }
    //Задать рег выражение для логина
    if(pLeName->text()==""||pLeName->text()==" "){
        QMessageBox::information(this,tr("Сообщение"),tr("Вы забыли указать имя!"));
        return;
    }
    emit clickedOk(pLeName->text(),pLePassword->text(),this);
}

