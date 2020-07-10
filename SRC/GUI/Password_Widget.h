#pragma once
#include <QtWidgets>

class Password_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Password_Widget(QWidget *parent = nullptr);

signals:
    void clickedOk(const QString&,const QString&);
    void clickedCancel();

private slots:
    void slotClickedOk();

private:
    QPushButton* pBtnOK;
    QPushButton* pBtnCancel;
    QLineEdit* pLeName;
    QLineEdit* pLePassword;
    QLineEdit* pLePasswordConfirmation;
};

