#pragma once
#include <QWidget>
#include <QTableWidget>

class Money_Repositary_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Money_Repositary_Widget(QWidget *parent = nullptr);

signals:

private:
    QTableWidget* pTable;

};


