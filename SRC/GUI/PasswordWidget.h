#pragma once
#include <QtWidgets>

class PasswordWidget : public QWidget{
    Q_OBJECT
public:
    explicit PasswordWidget(QWidget *parent = nullptr);
signals:
    void clickedOk(const QString&,const QString&);
    void clickedCancel();
    void close();

private slots:
    void slotClickedOk();

private:
    QPushButton* pBtnOK;
    QPushButton* pBtnCancel;
    QLineEdit* pLeName;
    QLineEdit* pLePassword;
    QLineEdit* pLePasswordConfirmation;

    void closeEvent(QCloseEvent* event);
};

