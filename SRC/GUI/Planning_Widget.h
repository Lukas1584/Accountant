#pragma once
#include <QtWidgets>
#include "SRC/BusinessLogic/BusinessLogic.h"

class Planning_Widget : public QWidget
{
    Q_OBJECT
public:
    Planning_Widget(std::shared_ptr<AbstractBusinessLogic> pLogic,QWidget *parent = nullptr);

signals:

private:
    std::shared_ptr<AbstractBusinessLogic> pLogic;
};

