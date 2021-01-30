#pragma once
#include <QtWidgets>

class PasswordWidget : public QDialog{
    Q_OBJECT
public:
    PasswordWidget();
signals:
    void clickedOk(const QString&,const QString&,PasswordWidget*);

private slots:
    void slotClickedOk();

private:
    QPushButton* pBtnOK;
    QLineEdit* pLeName;
    QLineEdit* pLePassword;
    QLineEdit* pLePasswordConfirmation;

    void drawWindow();
};

