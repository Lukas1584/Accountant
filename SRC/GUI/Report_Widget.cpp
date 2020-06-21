#include "Report_Widget.h"


Report_Widget::Report_Widget(QWidget *parent) : QWidget(parent)
{
    QPushButton* but=new QPushButton("Report");
    QVBoxLayout* box=new QVBoxLayout;
    box->addWidget(but);
    setLayout(box);
}

//QSortFilterProxyModel proxyModel;
//proxyModel.setSourceModel(pModel);
//proxyModel.setFilterRegExp(QRegExp("", Qt::CaseInsensitive,QRegExp::FixedString));
//proxyModel.setFilterKeyColumn(1);
//proxyModel.setFilterWildcard("*");
