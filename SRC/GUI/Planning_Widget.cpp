#include "Planning_Widget.h"


Planning_Widget::Planning_Widget(std::shared_ptr<AbstractBusinessLogic> logic, QWidget *parent) : QWidget(parent),pLogic(logic)
{
    QPushButton* but=new QPushButton("Planning");
    QVBoxLayout* box=new QVBoxLayout;
    box->addWidget(but);
    setLayout(box);
}
