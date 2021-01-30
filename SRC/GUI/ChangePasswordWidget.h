#pragma once
#include <QtWidgets>

class ChangePasswordWidget : public QDialog{
    Q_OBJECT
public:
    ChangePasswordWidget();

signals:
    void clickedOk(const QString&,const QString&);

private slots:
    void slotClickedOk();

private:
    QPushButton* pBtnOK;
    QLineEdit* pLeOldPassword;
    QLineEdit* pLePassword;
    QLineEdit* pLePasswordConfirmation;
    void drawWindow();
};

