#include "UserWidget.h"

UserWidget::UserWidget(std::shared_ptr<AbstractBusinessLogic> logic, QWidget* parent) : QWidget(parent), pLogic(logic){
    drawWindow();
    connectButtons();
    setStartView();
}

void UserWidget::drawWindow(){
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
}

void UserWidget::connectButtons(){
    QObject::connect(pBtnNewUser,SIGNAL(clicked()),SLOT(newUserClicked()));
    QObject::connect(pBtnLogIn,SIGNAL(clicked()),SLOT(logIn()));
    QObject::connect(pBtnChangeUser,SIGNAL(clicked()),SLOT(changeUser()));
    QObject::connect(pBtnDeleteUser,SIGNAL(clicked()),SLOT(deleteUser()));
    QObject::connect(pBtnChangePassword,SIGNAL(clicked()),SLOT(changePassword()));
    QObject::connect(pCbxUserName,SIGNAL(currentIndexChanged(int)),SLOT(clearPassword()));
}

void UserWidget::clearPassword(){
    pLedPassword->clear();
}

void UserWidget::setStartView(){
    emit exitUser();
    pCbxUserName->clear();
    pCbxUserName->addItems(convertToQstringList(pLogic->getUsersNames()));
    if(!pCbxUserName->count())
        pBtnLogIn->setEnabled(false);
    else pBtnLogIn->setEnabled(true);
    pBtnNewUser->setEnabled(true);
    pBtnDeleteUser->setEnabled(true);
    pCbxUserName->setEnabled(true);
    pLedPassword->setEnabled(true);
    pBtnChangeUser->setEnabled(false);
    pBtnChangePassword->setEnabled(false);
}

void UserWidget::newUserClicked(){
    PasswordWidget wdgPassword;
    wdgPassword.show();
    QObject::connect(&wdgPassword,SIGNAL(clickedOk(const QString&,const QString&,PasswordWidget*)),
                     SLOT(addUser(const QString&,const QString&)));
    wdgPassword.exec();
}

void UserWidget::addUser(const QString& login,const QString& password){
    if(pLogic->isUserCreated(login.toStdString(),password.toStdString())){
        pCbxUserName->clear();
        pCbxUserName->addItems(convertToQstringList(pLogic->getUsersNames()));
        setWorkView();
        emit dataIsLoaded();
    }
    else {
        QMessageBox::information(this,tr("Сообщение"),tr("Пользователь с таким именем уже существует"));
        newUserClicked();
    }
}

void UserWidget::logIn(){
    if(pLogic->loadData(pCbxUserName->currentText().toStdString(),pLedPassword->text().toStdString())){
        setWorkView();
        emit dataIsLoaded();
    }
    else {
        QMessageBox::information(this,tr("Сообщение"),tr("Неверный пароль!"));
        pLedPassword->clear();
    }
}

void UserWidget::setWorkView(){
    pBtnChangeUser->setEnabled(true);
    pBtnNewUser->setEnabled(false);
    pBtnLogIn->setEnabled(false);
    pBtnDeleteUser->setEnabled(false);
    pCbxUserName->setEnabled(false);
    pLedPassword->setEnabled(false);
    pBtnChangePassword->setEnabled(true);
}

void UserWidget::changeUser(){
    pLogic->clearData();
    clearPassword();
    setStartView();
}

void UserWidget::deleteUser(){
    if(pLogic->deleteUser(pCbxUserName->currentText().toStdString(),pLedPassword->text().toStdString()))
        setStartView();
    else {
        QMessageBox::information(this,tr("Сообщение"),tr("Неверный пароль!"));
        pLedPassword->clear();
    }
}

void UserWidget::changePassword(){
    ChangePasswordWidget wdgChangePassword;
    wdgChangePassword.show();
    QObject::connect(&wdgChangePassword,SIGNAL(clickedOk(const QString&,const QString&)),
                     SLOT(changingPassword(const QString&,const QString&)));
    wdgChangePassword.exec();
}

void UserWidget::changingPassword(const QString &oldPassword, const QString &newPassword){
    if(pLogic->changePassword(pCbxUserName->currentText().toStdString(),oldPassword.toStdString(),newPassword.toStdString())){
        QMessageBox::information(this,tr("Сообщение"),tr("Пароль изменен"));
    }
    else {
        QMessageBox::information(this,tr("Сообщение"),tr("Неверный пароль!"));
    }
}

QStringList UserWidget::convertToQstringList(const std::list<std::string>& listStd) const{
    QStringList list;
    for(const auto& i:listStd)
        list.push_back(QString::fromStdString(i));
    return list;
}
