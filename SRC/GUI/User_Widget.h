#pragma once
#include <QWidget>
#include <QtWidgets>

class User_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit User_Widget(QWidget *parent = nullptr);

signals:

private:
    QPushButton* pBtnNewUser;
    QPushButton* pBtnLogIn;
    QLineEdit* pLedPassword;
    QComboBox* pCbxUserName;

};


