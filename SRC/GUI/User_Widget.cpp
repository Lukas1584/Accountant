#include "User_Widget.h"

User_Widget::User_Widget(User_File_Operations* ufo) : QWidget(), pUserFileOperations(ufo)
{
    pBtnNewUser=new QPushButton(tr("Регистрация"));
    pBtnLogIn=new QPushButton(tr("Войти"));
    pBtnDeleteUser=new QPushButton(tr("Удалить пользователя"));
    pBtnChangeUser=new QPushButton(tr("Выйти/Сменить пользователя"));
    pBtnChangePassword=new QPushButton(tr("Сменить пароль"));

    pCbxUserName=new QComboBox;
    pLedPassword=new QLineEdit;
    pLedPassword->setEchoMode(QLineEdit::Password);

    pLblUserName=new QLabel(tr("Выберите имя из списка:"));
    pLblPassword=new QLabel(tr("Введите пароль:"));
    pGrdMain=new QGridLayout;

    QObject::connect(pBtnNewUser,SIGNAL(clicked()),SLOT(btnNewUserClicked()));
    QObject::connect(pBtnLogIn,SIGNAL(clicked()),SLOT(logIn()));
    QObject::connect(pBtnChangeUser,SIGNAL(clicked()),SLOT(changeUser()));
    QObject::connect(pBtnDeleteUser,SIGNAL(clicked()),SLOT(deleteUser()));
    QObject::connect(pBtnChangePassword,SIGNAL(clicked()),SLOT(changePassword()));

    pGrdMain->addWidget(pLblUserName,1,1,Qt::AlignRight);
    pGrdMain->addWidget(pLblPassword,2,1,Qt::AlignRight);
    pGrdMain->addWidget(pCbxUserName,1,2);
    pGrdMain->addWidget(pLedPassword,2,2);
    pGrdMain->addWidget(pBtnNewUser,1,3);
    pGrdMain->addWidget(pBtnLogIn,2,3);
    pGrdMain->addWidget(pBtnChangeUser,4,2);
    pGrdMain->addWidget(pBtnDeleteUser,4,1);
    pGrdMain->addWidget(pBtnChangePassword,4,3);
    pGrdMain->setRowStretch(3,1);
    pGrdMain->setColumnStretch(4,3);
    pGrdMain->setRowStretch(5,12);
    pGrdMain->setColumnStretch(0,1);
    pGrdMain->setRowStretch(0,4);
    setLayout(pGrdMain);

    setStartView();
}

void User_Widget::setStartView(){
    emit exitUser();
    pCbxUserName->clear();
    pCbxUserName->addItems(pUserFileOperations->getUsersNames());
    pBtnLogIn->setEnabled(true);
    if(!pCbxUserName->count()){
        pBtnLogIn->setEnabled(false);
    }
    pBtnNewUser->setEnabled(true);
    pBtnDeleteUser->setEnabled(true);
    pCbxUserName->setEnabled(true);
    pLedPassword->setEnabled(true);
    pBtnChangeUser->setEnabled(false);
    pBtnChangePassword->setEnabled(false);
}

void User_Widget::btnNewUserClicked(){
    emit disableMainWindow();
    wdgPassword=new Password_Widget();
    wdgPassword->show();
    QObject::connect(wdgPassword,SIGNAL(clickedOk(QString,QString)),SLOT(addUser(QString,QString)));
    QObject::connect(wdgPassword,SIGNAL(clickedCancel()),SIGNAL(enableMainWindow()));
}

void User_Widget::nameAlreadyExists(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this,tr("Сообщение"),tr("Пользователь с таким именем уже существует"));
    Q_UNUSED(reply);
    btnNewUserClicked();
}

void User_Widget::addUser(QString login,QString password){
    delete wdgPassword;
    wdgPassword=nullptr;
    if(pUserFileOperations->isUserCreated(login,password)){
        pCbxUserName->clear();
        pCbxUserName->addItems(pUserFileOperations->getUsersNames());
        setWorkView();
        emit enableMainWindow();
    }
    else nameAlreadyExists();
}

void User_Widget::logIn(){
    pUserFileOperations->loadData(pCbxUserName->currentText(),pLedPassword->text());
}

void User_Widget::wrongPassword(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this,tr("Сообщение"),tr("Неверный пароль!"));
    Q_UNUSED(reply);
    pLedPassword->clear();
}

void User_Widget::setWorkView(){
    pBtnChangeUser->setEnabled(true);
    pBtnNewUser->setEnabled(false);
    pBtnLogIn->setEnabled(false);
    pBtnDeleteUser->setEnabled(false);
    pCbxUserName->setEnabled(false);
    pLedPassword->setEnabled(false);
    pBtnChangePassword->setEnabled(true);
}

void User_Widget::changeUser(){
    pUserFileOperations->clearData();
    setStartView();
}

void User_Widget::deleteUser(){
    pUserFileOperations->deleteUser(pCbxUserName->currentText(),pLedPassword->text());
    setStartView();
}

void User_Widget::changePassword(){
    emit disableMainWindow();
    wdgChangePassword=new Change_Password_Widget();
    wdgChangePassword->show();
    QObject::connect(wdgChangePassword,SIGNAL(clickedOk(QString,QString)),SLOT(changingPassword(QString,QString)));
    QObject::connect(wdgChangePassword,SIGNAL(clickedCancel()),SIGNAL(enableMainWindow()));
}

void User_Widget::changingPassword(QString oldPassword,QString newPassword){
    delete wdgChangePassword;
    wdgChangePassword=nullptr;
    if(pUserFileOperations->changedPassword(pCbxUserName->currentText(),oldPassword,newPassword)){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this,tr("Сообщение"),tr("Пароль изменен"));
        Q_UNUSED(reply);
    }
    emit enableMainWindow();
}
