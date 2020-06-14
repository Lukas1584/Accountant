#include "User_Widget.h"
#include <QtGui>


User_Widget::User_Widget(User_File_Operations* ufo) : QWidget(), pUserFileOperations(ufo)
{
    pBtnNewUser=new QPushButton(tr("Регистрация"));
    pBtnLogIn=new QPushButton(tr("Войти"));
    pBtnExit=new QPushButton(tr("Сменить пользователя"));

    pCbxUserName=new QComboBox;
    pLedPassword=new QLineEdit;
    pLedPassword->setEchoMode(QLineEdit::Password);

    pLblUserName=new QLabel(tr("Выберите имя из списка:"));
    pLblPassword=new QLabel(tr("Введите пароль:"));
    pGrdMain=new QGridLayout;

    QObject::connect(pBtnNewUser,SIGNAL(clicked()),this,SLOT(btnNewUserClicked()));
    QObject::connect(this,SIGNAL(addUser(const QString,const QString)),pUserFileOperations,SLOT(userCreation(const QString&,const QString&)));
    QObject::connect(pBtnLogIn,SIGNAL(clicked()),this,SLOT(slotLogIn()));

    setStartView();
}

void User_Widget::setStartView(){

    pCbxUserName->addItems(pUserFileOperations->getUsersNames());
    pGrdMain->addWidget(pLblUserName,1,1,Qt::AlignRight);
    pGrdMain->addWidget(pLblPassword,2,1,Qt::AlignRight);
    pGrdMain->addWidget(pCbxUserName,1,2);
    pGrdMain->addWidget(pLedPassword,2,2);
    pGrdMain->addWidget(pBtnLogIn,1,3);
    pGrdMain->addWidget(pBtnNewUser,2,3);
    pGrdMain->setColumnStretch(4,3);
    pGrdMain->setRowStretch(4,3);
    pGrdMain->setColumnStretch(0,1);
    pGrdMain->setRowStretch(0,1);

    setLayout(pGrdMain);
}
void User_Widget::setWorkView(){
//При входе пользователем в свою БД, вид ока User будет с кнопкой выход/сменить пользователя

}

void User_Widget::btnNewUserClicked(){
    wdgPassword=new Password_Widget();
    wdgPassword->show();
    QObject::connect(wdgPassword,SIGNAL(clickedOk(QString,QString)),this,SLOT(slotAddUser(QString,QString)));
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
}

void User_Widget::slotLogIn(){
    emit logIn(pCbxUserName->currentText(),pLedPassword->text());
}
