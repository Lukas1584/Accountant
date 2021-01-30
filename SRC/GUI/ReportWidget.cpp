#include "ReportWidget.h"

ReportWidget::ReportWidget(std::shared_ptr<AbstractBusinessLogic> logic, QWidget *parent) : QWidget(parent),pLogic(logic){
    drawWindow();
    connectButtons();
}

void ReportWidget::drawWindow(){
    pGraphicWidget=new GraphicWidget(pLogic,this);
    pGraphicWidget->hide();

    pTable=new QTableWidget(this);
    pTable->installEventFilter(this);

    pBtnSaveTxt=new QPushButton(tr("Сохранить TXT"));
    pBtnSavePDF=new QPushButton(tr("Сохранить в PDF"));
    pBtnPrint=new QPushButton(tr("Печать"));
    pBtnChart=new QPushButton(tr("График"));
    pBtnReset=new QPushButton(tr("Сбросить фильтр"));

    QVBoxLayout* pVbxButtons=new QVBoxLayout;
    pVbxButtons->addWidget(pBtnSaveTxt);
    pVbxButtons->addWidget(pBtnSavePDF);
    pVbxButtons->addWidget(pBtnPrint);
    pVbxButtons->addWidget(pBtnChart);
    pVbxButtons->addStretch(1);

    QLabel* pLblDateFrom=new QLabel(tr("От:"));
    pTimeEditFrom=new QDateEdit();
    QLabel* pLblDateTo=new QLabel(tr("До:"));
    pTimeEditTo=new QDateEdit();
    QVBoxLayout* pVbxDate=new QVBoxLayout;
    pVbxDate->addWidget(pLblDateFrom);
    pVbxDate->addWidget(pTimeEditFrom);
    pVbxDate->addWidget(pLblDateTo);
    pVbxDate->addWidget(pTimeEditTo);
    pVbxDate->addStretch(1);

    QLabel* pLblType=new QLabel(tr("Тип:"));
    pChbxTypeProfit=new QCheckBox(tr("Прибыль"));
    pChbxTypeLoss=new QCheckBox(tr("Убыток"));
    QVBoxLayout* pVbxType=new QVBoxLayout;
    pVbxType->addWidget(pLblType);
    pVbxType->addWidget(pChbxTypeProfit);
    pVbxType->addWidget(pChbxTypeLoss);
    pVbxType->addStretch(1);

    QLabel* pLblCategory=new QLabel(tr("Категория:"));
    pCbxCategory=new QComboBox;
    pModelCategory = new QStandardItemModel(0, 1);
    pCbxCategory->setModel(pModelCategory);
    QVBoxLayout* pVbxCategory=new QVBoxLayout;
    pVbxCategory->addWidget(pLblCategory);
    pVbxCategory->addWidget(pCbxCategory);
    pVbxCategory->addStretch(1);

    QLabel* pLblDescription=new QLabel(tr("Описание:"));
    pCbxDescription=new QComboBox;
    pModelDescription = new QStandardItemModel(0, 1);
    pCbxDescription->setModel(pModelDescription);
    QVBoxLayout* pVbxDescription=new QVBoxLayout;
    pVbxDescription->addWidget(pLblDescription);
    pVbxDescription->addWidget(pCbxDescription);
    pVbxDescription->addStretch(1);

    QLabel* pLblSumFrom=new QLabel(tr("Сумма от:"));
    pLineEditSumFrom=new QLineEdit;
    QLabel* pLblSumTo=new QLabel(tr("Сумма до:"));
    pLineEditSumTo=new QLineEdit;
    QVBoxLayout* pVbxSum=new QVBoxLayout;
    pVbxSum->addWidget(pLblSumFrom);
    pVbxSum->addWidget(pLineEditSumFrom);
    pVbxSum->addWidget(pLblSumTo);
    pVbxSum->addWidget(pLineEditSumTo);
    pVbxSum->addStretch(1);

    QLabel* pLblCurrency=new QLabel(tr("Валюта:"));
    pCbxCurrency=new QComboBox;
    pModelCurrency = new QStandardItemModel(0, 1);
    pCbxCurrency->setModel(pModelCurrency);
    QVBoxLayout* pVbxCurrency=new QVBoxLayout;
    pVbxCurrency->addWidget(pLblCurrency);
    pVbxCurrency->addWidget(pCbxCurrency);
    pVbxCurrency->addStretch(1);

    QHBoxLayout* pHbxFilter=new QHBoxLayout;
    pHbxFilter->addLayout(pVbxDate,2);
    pHbxFilter->addLayout(pVbxType,1);
    pHbxFilter->addLayout(pVbxCategory,4);
    pHbxFilter->addLayout(pVbxDescription,4);
    pHbxFilter->addLayout(pVbxSum,2);
    pHbxFilter->addLayout(pVbxCurrency,1);

    QHBoxLayout* pHbxButtonsFilter=new QHBoxLayout;
    pHbxButtonsFilter->addWidget(pBtnReset);
    pHbxButtonsFilter->addWidget(pBtnChart);

    QVBoxLayout* pVbxFilter=new QVBoxLayout;
    pVbxFilter->addLayout(pHbxFilter);
    pVbxFilter->addLayout(pHbxButtonsFilter);

    QHBoxLayout* pHbxButtonsAndFilter=new QHBoxLayout;
    pHbxButtonsAndFilter->addLayout(pVbxFilter);
    pHbxButtonsAndFilter->addLayout(pVbxButtons);

    QVBoxLayout* pVbxMain=new QVBoxLayout;
    pVbxMain->addLayout(pHbxButtonsAndFilter,1);
    pVbxMain->addWidget(pGraphicWidget,6);
    pVbxMain->addWidget(pTable,6);
    setLayout(pVbxMain);
}

void ReportWidget::connectButtons(){
    QObject::connect(pChbxTypeProfit,SIGNAL(clicked()),SLOT(fillComboBoxCategory()));
    QObject::connect(pChbxTypeLoss,SIGNAL(clicked()),SLOT(fillComboBoxCategory()));

    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(categoryChecked(QStandardItem*)));
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(fillComboBoxDescription()));

    QObject::connect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),SLOT(descriptionChecked(QStandardItem*)));
    QObject::connect(pModelCurrency,SIGNAL(itemChanged(QStandardItem*)),SLOT(currencyChecked(QStandardItem*)));

    QObject::connect(pBtnReset,SIGNAL(clicked()),SLOT(resetFilter()));
    QObject::connect(pBtnSaveTxt,SIGNAL(clicked()),SLOT(saveTxt()));
    QObject::connect(pBtnSavePDF,SIGNAL(clicked()),SLOT(savePDF()));
    QObject::connect(pBtnPrint,SIGNAL(clicked()),SLOT(btnPrintClicked()));
    QObject::connect(pBtnChart,SIGNAL(clicked()),SLOT(btnChartClicked()));

    QObject::connect(pTimeEditFrom,SIGNAL(dateChanged(const QDate&)),SLOT(filter()));
    QObject::connect(pTimeEditTo,SIGNAL(dateChanged(const QDate&)),SLOT(filter()));
    QObject::connect(pChbxTypeProfit,SIGNAL(clicked()),SLOT(filter()));
    QObject::connect(pChbxTypeLoss,SIGNAL(clicked()),SLOT(filter()));
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(filter()));
    QObject::connect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),SLOT(filter()));
    QObject::connect(pModelCurrency,SIGNAL(itemChanged(QStandardItem*)),SLOT(filter()));
    QObject::connect(pLineEditSumFrom,SIGNAL(textChanged(const QString&)),SLOT(filter()));
    QObject::connect(pLineEditSumTo,SIGNAL(textChanged(const QString&)),SLOT(filter()));
}

void ReportWidget::updateTable(){
    unsigned int rows=pLogic->rowsCountReport();
    pTable->setRowCount(rows);
    pTable->setColumnCount(pLogic->columnsCount());
    for(unsigned int row = 0;row<rows;row++){
        RecordString rec=pLogic->getReport(row);
        QTableWidgetItem* item0 = new QTableWidgetItem(rec.getDate().c_str());
        pTable->setItem(row,0,item0);
        QTableWidgetItem* item1 = new QTableWidgetItem(rec.getType().c_str());
        pTable->setItem(row,1,item1);
        QTableWidgetItem* item2 = new QTableWidgetItem(rec.getCategory().c_str());
        pTable->setItem(row,2,item2);
        QTableWidgetItem* item3 = new QTableWidgetItem(rec.getDescription().c_str());
        pTable->setItem(row,3,item3);
        QTableWidgetItem* item4 = new QTableWidgetItem(QString::number(rec.getSum()));
        pTable->setItem(row,4,item4);
        QTableWidgetItem* item5 = new QTableWidgetItem(rec.getCurrency().c_str());
        pTable->setItem(row,5,item5);
    }
    setTableHeader();
    setTableDimensions();
}

void ReportWidget::setTableHeader(){
    std::vector<std::string> header{"Дата","Тип","Категория","Описание","Сумма","Валюта"};
    unsigned int columnsCount=header.size();
    for(unsigned int i=0;i<columnsCount;i++){
        QTableWidgetItem* item=new QTableWidgetItem(header[i].c_str());
        pTable->setHorizontalHeaderItem(i,item);
    }
    pTable->verticalHeader()->hide();
}

void ReportWidget::setTableDimensions(){
    pTable->setColumnWidth(0, pTable->width() * 0.1);
    pTable->setColumnWidth(1, pTable->width() * 0.1);
    pTable->setColumnWidth(2, pTable->width() * 0.28);
    pTable->setColumnWidth(3, pTable->width() * 0.3);
    pTable->setColumnWidth(4, pTable->width() * 0.1);
    pTable->setColumnWidth(5, pTable->width() * 0.1);
}

bool ReportWidget::eventFilter(QObject* , QEvent *pEvent){
    if(pEvent->type() == QEvent::Resize )
        setTableDimensions();
    return false;
}

void ReportWidget::filter(){
    pLogic->filter(pTimeEditFrom->date().toString("yyyy-MM-dd").toStdString(),
                      pTimeEditTo->date().toString("yyyy-MM-dd").toStdString(),
                      typeToReport(),
                      getComboBoxCheckedList(pCbxCategory),
                      getComboBoxCheckedList(pCbxDescription),
                      pLineEditSumFrom->text().toFloat(),
                      pLineEditSumTo->text().toDouble(),
                      getComboBoxCheckedList(pCbxCurrency));
    updateTable();
}

std::pair<bool,bool> ReportWidget::typeToReport() const{
    std::pair<bool,bool> type {false,false};
    if (pChbxTypeProfit->isChecked())
        type.first=true;
    if(pChbxTypeLoss->isChecked())
        type.second=true;
    return type;
}

void ReportWidget::fillFields(){
    pChbxTypeProfit->setChecked(true);
    pChbxTypeLoss->setChecked(true);
    fillComboBoxCategory();
    fillComboBoxDescription();
    fillDate();
    fillSum();
    fillComboBoxCurrency();
}

void ReportWidget::fillComboBoxCurrency(){
    std::list<std::string> list=pLogic->getAllCurrencies();
    fillComboBox(pModelCurrency,list);
}

void ReportWidget::fillDate(){
    std::pair<std::string,std::string> minMax=pLogic->dateMinMax();
    pTimeEditFrom->setDate(QDate::fromString(QString::fromStdString(minMax.first),"yyyy-MM-dd"));
    pTimeEditTo->setDate(QDate::fromString(QString::fromStdString(minMax.second),"yyyy-MM-dd"));
}

void ReportWidget::fillSum(){
    std::pair<double,double> minMax=pLogic->sumMinMax();
    pLineEditSumFrom->setText(QString::number(minMax.first));
    pLineEditSumTo->setText(QString::number(minMax.second));
}

void ReportWidget::fillComboBoxCategory(){
    QObject::disconnect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(categoryChecked(QStandardItem*)));
    std::list<std::string> list=pLogic->getReportCategories(pChbxTypeProfit->isChecked(),pChbxTypeLoss->isChecked());
    fillComboBox(pModelCategory,list);
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(categoryChecked(QStandardItem*)));
}

void ReportWidget::fillComboBoxDescription() {
    std::vector<std::string> listCategories;
    listCategories=getComboBoxCheckedList(pCbxCategory);
    std::list<std::string> listDescriptions;
    listDescriptions=pLogic->getReportDescriptions(listCategories);
    fillComboBox(pModelDescription,listDescriptions);
}

void ReportWidget::fillComboBox(QStandardItemModel* model,std::list<std::string>& list){
    list.insert(list.begin(),"Все");
    model->setRowCount(static_cast<int>(list.size()));
    int row=0;
    for (const auto& i:list){
        QStandardItem* item = new QStandardItem(i.c_str());
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Checked, Qt::CheckStateRole);
        model->setItem(row, 0, item);
        row++;
    }
}

std::vector<std::string> ReportWidget::getComboBoxCheckedList(const QComboBox* combobox) const{
    std::vector<std::string> list;
    int count=combobox->count();
    for(int i=0; i<count; i++){
        QModelIndex index = combobox->model()->index(i, 0);
        if(index.data(Qt::CheckStateRole) == Qt::Checked)
            list.push_back(index.data(Qt::DisplayRole).toString().toStdString());
    }
    return list;
}

void ReportWidget::categoryChecked(QStandardItem* item){
    QObject::disconnect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(categoryChecked(QStandardItem*)));
    checkControl(pModelCategory,item);
    QObject::connect(pModelCategory,SIGNAL(itemChanged(QStandardItem*)),SLOT(categoryChecked(QStandardItem*)));
}

void ReportWidget::descriptionChecked(QStandardItem* item){
    QObject::disconnect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(descriptionChecked(QStandardItem*)));
    checkControl(pModelDescription,item);
    QObject::connect(pModelDescription,SIGNAL(itemChanged(QStandardItem*)),SLOT(descriptionChecked(QStandardItem*)));
}

void ReportWidget::currencyChecked(QStandardItem* item){
    QObject::disconnect(pModelCurrency,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(currencyChecked(QStandardItem*)));
    checkControl(pModelCurrency,item);
    QObject::connect(pModelCurrency,SIGNAL(itemChanged(QStandardItem*)),SLOT(currencyChecked(QStandardItem*)));
}

void ReportWidget::checkControl(QStandardItemModel* model,QStandardItem* item){
    QModelIndex index = model->index(item->index().row(),0);
    if(item->index().row()==0){
        if(index.data(Qt::CheckStateRole) == Qt::Checked)
            setCheckAll(model,Qt::Checked);
        else
            setCheckAll(model,Qt::Unchecked);
    }
    else{
        if(index.data(Qt::CheckStateRole) == Qt::Unchecked){
            QModelIndex indexAll = model->index(0, 0);
            model->setData(indexAll,Qt::Unchecked, Qt::CheckStateRole);
        }
    }
}

void ReportWidget::setCheckAll(QStandardItemModel* model,Qt::CheckState state){
    int rowCount=model->rowCount();
    for(int i=0; i<rowCount; i++){
        QModelIndex index = model->index(i, 0);
        model->setData(index,state, Qt::CheckStateRole);
    }
}

void ReportWidget::resetFilter(){
    fillFields();
    filter();
}

void ReportWidget::saveTxt(){
    QString fieName = QFileDialog::getSaveFileName(0,tr("Сохранить txt"),"","*.txt");
    pLogic->saveReportTxt(fieName.toStdString(),QDate::currentDate().toString("yyyy-MM-dd").toStdString());
}

void ReportWidget::savePDF(){
    QString fieName = QFileDialog::getSaveFileName(0,tr("Сохранить pdf"),"","*.pdf");
    pLogic->saveReportPDF(fieName.toStdString(),QDate::currentDate().toString("yyyy-MM-dd").toStdString());
}

void ReportWidget::btnPrintClicked(){
      pLogic->printReport(QDate::currentDate().toString("yyyy-MM-dd").toStdString());
//    printer=std::make_unique<QPrinter>(QPrinter::PrinterResolution);
//    QPrintPreviewDialog printDialog(printer.get());
//    QObject::connect(&printDialog,SIGNAL(paintRequested(QPrinter*)),SLOT(printReport()));
//    printDialog.showMaximized();
//    printDialog.exec();
//    printer.reset(nullptr);
}

void ReportWidget::printReport(){
    QPainter painter(printer.get());
    painter.setFont(QFont(font,fontSize));
    calculatePageParameters();
    double yPosition=0;
    printHeader(painter,yPosition);
    printTable(painter,yPosition);
}

void ReportWidget::printHeader(QPainter& painter,double& yPosition){
    yPosition=verticalBorder+leading;
    painter.drawText(0.48*pageWidth,yPosition,"Отчет");
    nextRow(yPosition);
    QString str="Пользователь: "+ QString::fromStdString(pLogic->getUserName());
    painter.drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    str="Дата отчета: "+QDate::currentDate().toString("yyyy-MM-dd");
    painter.drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    str="Установки фильтра:";
    painter.drawText(0.45*pageWidth,yPosition,str);
    nextRow(yPosition);
    str="Дата от: "+pTimeEditFrom->text()+"    Дата до: "+pTimeEditTo->text();
    painter.drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    str="Тип: ";
    if((pChbxTypeProfit->isChecked()==true)&&(pChbxTypeLoss->isChecked()==false)) str+="Прибыль";
    if((pChbxTypeProfit->isChecked()==false)&&(pChbxTypeLoss->isChecked()==true)) str+="Убыток";
    if((pChbxTypeProfit->isChecked()==true)&&(pChbxTypeLoss->isChecked()==true)) str+="все";
    painter.drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    str="Сумма от: "+pLineEditSumFrom->text()+" Сумма до: "+pLineEditSumTo->text();
    painter.drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    str="Валюты: ";
    painter.drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    printComboBoxCheckedList(pCbxCurrency,painter,yPosition);
    str="Категории: ";
    painter.drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    printComboBoxCheckedList(pCbxCategory,painter,yPosition);
    str="Описания: ";
    painter.drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    printComboBoxCheckedList(pCbxDescription,painter,yPosition);
}

void ReportWidget::nextRow(double& yPosition)const{
    yPosition+=leading;
    if(yPosition>(pageHeight-verticalBorder)){
        printer->newPage();
        yPosition=verticalBorder+leading;
    }
}

void ReportWidget::printComboBoxCheckedList(const QComboBox* combobox,QPainter& painter,double& yPosition) const{
    if(combobox->model()->index(0,0).data(Qt::CheckStateRole)==Qt::Checked){
        painter.drawText(leftBorder,yPosition,"Все");
        nextRow(yPosition);
        return;
    }
    for(int i=1; i<combobox->count(); i++){
        QModelIndex index = combobox->model()->index(i, 0);
        if(index.data(Qt::CheckStateRole) == Qt::Checked){
            painter.drawText(leftBorder,yPosition,index.data(Qt::DisplayRole).toString());
            nextRow(yPosition);
        }
    }
}

void ReportWidget::printTable(QPainter& painter,double& yPosition){
    const double pageWidthWithoutBorders=(pageWidth-leftBorder-rightBorder);
    const double xType=0.15*pageWidthWithoutBorders;
    const double xCategory=0.28*pageWidthWithoutBorders;
    const double xDescription=0.54*pageWidthWithoutBorders;
    const double xSum=0.8*pageWidthWithoutBorders;
    const double xCurrency=0.92*pageWidthWithoutBorders;
    /*print table header*/
    painter.drawText(leftBorder,yPosition,pTable->horizontalHeaderItem(0)->data(Qt::DisplayRole).toString());
    painter.drawText(leftBorder+xType,yPosition,pTable->horizontalHeaderItem(1)->data(Qt::DisplayRole).toString());
    painter.drawText(leftBorder+xCategory,yPosition,pTable->horizontalHeaderItem(2)->data(Qt::DisplayRole).toString());
    painter.drawText(leftBorder+xDescription,yPosition,pTable->horizontalHeaderItem(3)->data(Qt::DisplayRole).toString());
    painter.drawText(leftBorder+xSum,yPosition,pTable->horizontalHeaderItem(4)->data(Qt::DisplayRole).toString());
    painter.drawText(leftBorder+xCurrency,yPosition,pTable->horizontalHeaderItem(5)->data(Qt::DisplayRole).toString());
    nextRow(yPosition);
    /*print table*/
    for(int row = 0;row<pTable->rowCount();++row){
        painter.drawText(leftBorder,yPosition,pTable->item(row,0)->data(Qt::DisplayRole).toString());
        painter.drawText(leftBorder+xType,yPosition,pTable->item(row,1)->data(Qt::DisplayRole).toString());
        painter.drawText(leftBorder+xCategory,yPosition,pTable->item(row,2)->data(Qt::DisplayRole).toString());
        painter.drawText(leftBorder+xDescription,yPosition,pTable->item(row,3)->data(Qt::DisplayRole).toString());
        painter.drawText(leftBorder+xSum,yPosition,pTable->item(row,4)->data(Qt::DisplayRole).toString());
        painter.drawText(leftBorder+xCurrency,yPosition,pTable->item(row,5)->data(Qt::DisplayRole).toString());
        yPosition+=leading;
        if(yPosition>(pageHeight-verticalBorder)&&(row!=(pTable->rowCount()-1))){
            printer->newPage();
            yPosition=verticalBorder+leading;
            /*print table header*/
            painter.drawText(leftBorder,yPosition,pTable->horizontalHeaderItem(0)->data(Qt::DisplayRole).toString());
            painter.drawText(leftBorder+xType,yPosition,pTable->horizontalHeaderItem(1)->data(Qt::DisplayRole).toString());
            painter.drawText(leftBorder+xCategory,yPosition,pTable->horizontalHeaderItem(2)->data(Qt::DisplayRole).toString());
            painter.drawText(leftBorder+xDescription,yPosition,pTable->horizontalHeaderItem(3)->data(Qt::DisplayRole).toString());
            painter.drawText(leftBorder+xSum,yPosition,pTable->horizontalHeaderItem(4)->data(Qt::DisplayRole).toString());
            painter.drawText(leftBorder+xCurrency,yPosition,pTable->horizontalHeaderItem(5)->data(Qt::DisplayRole).toString());
            yPosition+=leading;
        }
    }
}

void ReportWidget::calculatePageParameters(){
    leading=2*QFont(font,fontSize).pointSize();
    pageWidth=printer->pageLayout().paintRect().width();
    pageHeight=printer->pageLayout().paintRect().height();
    leftBorder=0.12*pageWidth;
    rightBorder=0.024*pageWidth;
    verticalBorder=0.017*pageHeight;
}

void ReportWidget::btnChartClicked(){
    if(pTable->isHidden()==false){
        pTable->hide();
        pGraphicWidget->show();
        pBtnChart->setText("Таблица");
    }
    else {
        pTable->show();
        pGraphicWidget->hide();
        pBtnChart->setText("График");
    }
}
