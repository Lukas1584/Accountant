#include "User_Widget.h"


User_Widget::User_Widget(User_File_Operations* ufo) : QWidget(), pUserFileOperations(ufo)
{

    pBtnNewUser=new QPushButton(tr("Регистрация"));
    pBtnLogIn=new QPushButton(tr("Войти"));
    pBtnExit=new QPushButton(tr("Выйти"));
    pLedPassword=new QLineEdit;
    pLedPassword->setEchoMode(QLineEdit::Password);
    pCbxUserName=new QComboBox;
    pCbxUserName->addItems(pUserFileOperations->getUsersNames());


    QLabel* pLblUserName=new QLabel(tr("Выберите имя из списка:"));
    QLabel* pLblPassword=new QLabel(tr("Введите пароль:"));

    QObject::connect(pBtnNewUser,SIGNAL(clicked()),this,SLOT(btnNewUserClicked()));
    QObject::connect(this,SIGNAL(addUser(QString,QString)),pUserFileOperations,SLOT(userCreation(QString, QString)));

    QVBoxLayout* pVbx=new QVBoxLayout;
    pVbx->addStretch(1);
    pVbx->addWidget(pLblUserName);
    pVbx->addWidget(pCbxUserName);
    pVbx->addWidget(pLblPassword);
    pVbx->addWidget(pLedPassword);
    pVbx->addWidget(pBtnLogIn);
    pVbx->addStretch(1);
    pVbx->addWidget(pBtnNewUser);
    pVbx->addStretch(1);
    pVbx->addWidget(pBtnExit);
    pVbx->addStretch(5);

    QHBoxLayout* pHbx=new QHBoxLayout;
    pHbx->addStretch(1);
    pHbx->addLayout(pVbx,2);
    pHbx->addStretch(3);
    setLayout(pHbx);
}
void User_Widget::btnNewUserClicked(){
    QString login="Sergey";
    QString password="01234";
    emit addUser(login,password);
}
