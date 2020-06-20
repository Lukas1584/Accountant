#include "Report_Widget.h"


Report_Widget::Report_Widget(QWidget *parent) : QWidget(parent)
{
    QPushButton* but=new QPushButton("Report");
    QVBoxLayout* box=new QVBoxLayout;
    box->addWidget(but);
    setLayout(box);
}
