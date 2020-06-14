#pragma once
#include <QObject>
#include <QWidget>
#include <QtWidgets>

class Password_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Password_Widget(QWidget *parent = nullptr);

signals:
    void clickedOk(QString,QString);

private slots:
    void slotClickedOk();
    void clickedCancel();

private:
    QPushButton* pBtnOK;
    QPushButton* pBtnCancel;
    QLineEdit* pLeName;
    QLineEdit* pLePassword;
    QLineEdit* pLePasswordConfirmation;
};

