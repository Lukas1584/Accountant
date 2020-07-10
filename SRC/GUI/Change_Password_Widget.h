#include <QObject>
#include <QtWidgets>

class Change_Password_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Change_Password_Widget(QWidget *parent = nullptr);

signals:
    void clickedOk(const QString&,const QString&);
    void clickedCancel();

private slots:
    void slotClickedOk();

private:
    QPushButton* pBtnOK;
    QPushButton* pBtnCancel;
    QLineEdit* pLeOldPassword;
    QLineEdit* pLePassword;
    QLineEdit* pLePasswordConfirmation;
};

