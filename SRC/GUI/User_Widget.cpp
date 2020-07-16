#include "User_Widget.h"

User_Widget::User_Widget(User_File_Operations *user,QWidget* parent) : QWidget(parent), pUserFileOperations(user)
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
    QGridLayout* pGrdMain=new QGridLayout;

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
    pCbxUserName->addItems(convertToStringist(pUserFileOperations->getUsersNames()));
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
    wdgPassword=std::make_shared<Password_Widget>();
    wdgPassword->show();
    QObject::connect(wdgPassword.get(),SIGNAL(clickedOk(QString,QString)),SLOT(addUser(QString,QString)));
    QObject::connect(wdgPassword.get(),SIGNAL(clickedCancel()),SLOT(cancelNewUser()));
    QObject::connect(wdgPassword.get(),SIGNAL(clickedCancel()),SLOT(cancelNewUser()));
}

void User_Widget::nameAlreadyExists(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this,tr("Сообщение"),tr("Пользователь с таким именем уже существует"));
    Q_UNUSED(reply);
    btnNewUserClicked();
}

void User_Widget::addUser(const QString& login,const QString& password){
    wdgPassword.reset();
    if(pUserFileOperations->isUserCreated(login.toStdString(),password.toStdString())){
        pCbxUserName->clear();
        pCbxUserName->addItems(convertToStringist(pUserFileOperations->getUsersNames()));
        setWorkView();
        emit enableMainWindow();
    }
    else nameAlreadyExists();
}
void User_Widget::cancelNewUser(){
    wdgPassword.reset();
    emit enableMainWindow();
}

void User_Widget::logIn(){
    pUserFileOperations->loadData(pCbxUserName->currentText().toStdString(),pLedPassword->text().toStdString());
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
    pUserFileOperations->deleteUser(pCbxUserName->currentText().toStdString(),pLedPassword->text().toStdString());
    setStartView();
}

void User_Widget::changePassword(){
    emit disableMainWindow();
    wdgChangePassword=std::make_shared<Change_Password_Widget>();
    wdgChangePassword->show();
    QObject::connect(wdgChangePassword.get(),SIGNAL(clickedOk(const QString&,const QString&)),SLOT(changingPassword(const QString&,const QString&)));
    QObject::connect(wdgChangePassword.get(),SIGNAL(clickedCancel()),SLOT(cancelChangePassword()));
}

void User_Widget::changingPassword(const QString &oldPassword, const QString &newPassword){
    wdgChangePassword.reset();
    wdgChangePassword=nullptr;
    if(pUserFileOperations->changedPassword(pCbxUserName->currentText().toStdString(),oldPassword.toStdString(),newPassword.toStdString())){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this,tr("Сообщение"),tr("Пароль изменен"));
        Q_UNUSED(reply);
    }
    emit enableMainWindow();
}

void User_Widget::cancelChangePassword(){
    wdgChangePassword.reset();
    wdgChangePassword=nullptr;
    emit enableMainWindow();
}

QStringList User_Widget::convertToStringist(const std::list<std::string> &listStd) const{
    QStringList list;
    for(const auto& i:listStd)
        list.push_back(QString::fromStdString(i));
    return list;
}
