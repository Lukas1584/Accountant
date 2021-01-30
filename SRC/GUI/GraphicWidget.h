#pragma once
#include <QComboBox>
#include <QtWidgets>
#include <QVBoxLayout>

#include "SRC/BusinessLogic/AbstractBusinessLogic.h"

class GraphicWidget : public QWidget
{
    Q_OBJECT
public:
    GraphicWidget(std::shared_ptr<AbstractBusinessLogic> logic,QWidget *parent);

signals:

private:
    std::shared_ptr<AbstractBusinessLogic> pLogic;
    QComboBox* pCbxCurrency;

    QStringList convertToQList(const std::list<std::string>& list)const;
};


