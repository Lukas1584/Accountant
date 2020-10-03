#include <QObject>
#include <QtWidgets>

class ChangePasswordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChangePasswordWidget(QWidget *parent = nullptr);

signals:
    void clickedOk(const QString&,const QString&);
    void clickedCancel();
    void close();

private slots:
    void slotClickedOk();

private:
    QPushButton* pBtnOK;
    QPushButton* pBtnCancel;
    QLineEdit* pLeOldPassword;
    QLineEdit* pLePassword;
    QLineEdit* pLePasswordConfirmation;
    void closeEvent(QCloseEvent* event);
};

