#include "Planning_Widget.h"


Planning_Widget::Planning_Widget(QWidget *parent) : QWidget(parent)
{
    QPushButton* but=new QPushButton("Planning");
    QVBoxLayout* box=new QVBoxLayout;
    box->addWidget(but);
    setLayout(box);
}
