#include "User_Widget.h"

User_Widget::User_Widget(User_File_Operations* ufo) : QWidget(), pUserFileOperations(ufo)
{
    pBtnNewUser=new QPushButton(tr("Регистрация"));
    pBtnLogIn=new QPushButton(tr("Войти"));

    pBtnDeleteUser=new QPushButton(tr("Удалить пользователя"));
    pBtnChangeUser=new QPushButton(tr("Выйти/Сменить пользователя"));

    pCbxUserName=new QComboBox;
    pLedPassword=new QLineEdit;
    pLedPassword->setEchoMode(QLineEdit::Password);

    pLblUserName=new QLabel(tr("Выберите имя из списка:"));
    pLblPassword=new QLabel(tr("Введите пароль:"));
    pGrdMain=new QGridLayout;

    QObject::connect(pBtnNewUser,SIGNAL(clicked()),this,SLOT(btnNewUserClicked()));
    QObject::connect(this,SIGNAL(addUser(const QString,const QString)),pUserFileOperations,SLOT(userCreation(const QString&,const QString&)));
    QObject::connect(pBtnLogIn,SIGNAL(clicked()),this,SLOT(slotLogIn()));
    QObject::connect(pBtnChangeUser,SIGNAL(clicked()),this,SLOT(changeUser()));

    setStartView();
}

void User_Widget::setStartView(){
    pCbxUserName->addItems(pUserFileOperations->getUsersNames());

    pBtnNewUser->setEnabled(true);
    pBtnLogIn->setEnabled(true);
    pBtnDeleteUser->setEnabled(true);
    pCbxUserName->setEnabled(true);
    pLedPassword->setEnabled(true);
    pBtnChangeUser->setEnabled(false);

    pGrdMain->addWidget(pLblUserName,1,1,Qt::AlignRight);
    pGrdMain->addWidget(pLblPassword,2,1,Qt::AlignRight);
    pGrdMain->addWidget(pCbxUserName,1,2);
    pGrdMain->addWidget(pLedPassword,2,2);
    pGrdMain->addWidget(pBtnNewUser,1,3);
    pGrdMain->addWidget(pBtnLogIn,2,3);
    pGrdMain->addWidget(pBtnChangeUser,4,2);
    pGrdMain->addWidget(pBtnDeleteUser,4,3);
    pGrdMain->setRowStretch(3,1);
    pGrdMain->setColumnStretch(4,3);
    pGrdMain->setRowStretch(5,12);
    pGrdMain->setColumnStretch(0,1);
    pGrdMain->setRowStretch(0,4);

    setLayout(pGrdMain);
}


void User_Widget::btnNewUserClicked(){
    wdgPassword=new Password_Widget();
    wdgPassword->show();
    QObject::connect(wdgPassword,SIGNAL(clickedOk(QString,QString)),this,SLOT(slotAddUser(QString,QString)));
    QObject::connect(wdgPassword,SIGNAL(enableMainWindow()),this,SLOT(enableMainWindowFromPassword()));
    emit disableMainWindow();
}

void User_Widget::nameAlreadyExists(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this,tr("Сообщение"),tr("Пользователь с таким именем уже существует"));
    btnNewUserClicked();
}

void User_Widget::slotAddUser(QString login,QString password){
    delete wdgPassword;
    wdgPassword=nullptr;
    emit addUser(login,password);
    emit enableMainWindow();
    pCbxUserName->clear();
    pCbxUserName->addItems(pUserFileOperations->getUsersNames());
}

void User_Widget::slotLogIn(){
    emit logIn(pCbxUserName->currentText(),pLedPassword->text());
}

void User_Widget::wrongPassword(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this,tr("Сообщение"),tr("Неверный пароль!"));
    pLedPassword->clear();
}

void User_Widget::enableMainWindowFromPassword(){
    emit enableMainWindow();
}

void User_Widget::setWorkView(){
    pBtnChangeUser->setEnabled(true);
    pBtnNewUser->setEnabled(false);
    pBtnLogIn->setEnabled(false);
    pBtnDeleteUser->setEnabled(false);
    pCbxUserName->setEnabled(false);
    pLedPassword->setEnabled(false);
}

void User_Widget::changeUser(){
    emit clearData();
    setStartView();
}
