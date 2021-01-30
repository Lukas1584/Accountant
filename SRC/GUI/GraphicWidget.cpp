#include "GraphicWidget.h"

GraphicWidget::GraphicWidget(std::shared_ptr<AbstractBusinessLogic> logic, QWidget *parent) : QWidget(parent),pLogic(logic){
    pCbxCurrency=new QComboBox;
    pCbxCurrency->addItems(convertToQList(pLogic->getAllCurrencies()));

    QVBoxLayout* pVbx=new QVBoxLayout;
    pVbx->addWidget(pCbxCurrency);
    setLayout(pVbx);
}

QStringList GraphicWidget::convertToQList(const std::list<std::string>& list) const{
    QStringList qList;
    for(const auto& i:list)
        qList.push_back(QString::fromStdString(i));
    return qList;
}
