#include "User_Widget.h"

User_Widget::User_Widget(QWidget *parent) : QWidget(parent)
{





    pBtnNewUser=new QPushButton(tr("Регистрация"));
    pBtnLogIn=new QPushButton(tr("Войти"));
    pLedPassword=new QLineEdit;
    pLedPassword->setEchoMode(QLineEdit::Password);
    pCbxUserName=new QComboBox;
    QLabel* pLblUserName=new QLabel(tr("Введите имя:"));
    QLabel* pLblPassword=new QLabel(tr("Введите пароль:"));


    QVBoxLayout* pVbx=new QVBoxLayout;
    pVbx->addStretch(1);
    pVbx->addWidget(pLblUserName);
    pVbx->addWidget(pCbxUserName);
    pVbx->addWidget(pLblPassword);
    pVbx->addWidget(pLedPassword);
    pVbx->addWidget(pBtnLogIn);
    pVbx->addWidget(pBtnNewUser);
    pVbx->addStretch(5);

    QHBoxLayout* pHbx=new QHBoxLayout;
    pHbx->addStretch(1);
    pHbx->addLayout(pVbx,2);
    pHbx->addStretch(3);
    setLayout(pHbx);
}
