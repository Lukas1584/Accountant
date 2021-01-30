#include "ReportPrint.h"

ReportPrint::ReportPrint(std::shared_ptr<Report>& report):pReport(report){
    printer=new QPrinter;



    printDialog=new QPrintPreviewDialog(printer);
    printDialog->setModal(true);
    printDialog->showMaximized();
    QObject::connect(printDialog,SIGNAL(paintRequested(QPrinter*)),SLOT(ReportPrint()));
}

ReportPrint::~ReportPrint(){
    delete printDialog;
    delete painter;
    delete printer;

}

void ReportPrint::calculatePageParameters(){
    leading=2*QFont(font.c_str(),fontSize).pointSize();
    pageWidth=printer->pageLayout().paintRect().width();
    pageHeight=printer->pageLayout().paintRect().height();
    leftBorder=0.12*pageWidth;
    rightBorder=0.024*pageWidth;
    verticalBorder=0.017*pageHeight;
}

//    printer=std::make_unique<QPrinter>(QPrinter::PrinterResolution);
//    QPrintPreviewDialog printDialog(printer.get());
//    QObject::connect(&printDialog,SIGNAL(paintRequested(QPrinter*)),SLOT(ReportPrint()));
//    printDialog.showMaximized();
//    printDialog.exec();
//    printer.reset(nullptr);

//void ReportWidget::ReportPrint(){
//    QPainter painter(printer.get());
//    painter.setFont(QFont(font,fontSize));
//    calculatePageParameters();
//    double yPosition=0;
//    printHeader(painter,yPosition);
//    printTable(painter,yPosition);
//}

void ReportPrint::printReport(const std::string& userName,const std::string& currentDate){

    //QPrintPreviewDialog printDialog(printer);
    //printDialog.showMaximized();
    //QObject::connect(&printDialog,SIGNAL(paintRequested(QPrinter*)),SLOT(ReportPrint()));
    double yPosition=0;
    printHeader(yPosition,userName,currentDate);
    printTable(yPosition);

   // printDialog->exec();

}
void ReportPrint::printReport(){
    painter=new QPainter(printer);
    painter->setFont(QFont(font.c_str(),fontSize));
    calculatePageParameters();

}

void ReportPrint::printHeader(double& yPosition,const std::string& userName,const std::string& currentDate){
    yPosition=verticalBorder+leading;
    painter->drawText(0.48*pageWidth,yPosition,"Отчет");
    nextRow(yPosition);
    QString str="Пользователь: "+ QString::fromStdString(userName);
    painter->drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    str="Дата отчета: "+QString::fromStdString(currentDate);
    painter->drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    str="Установки фильтра:";
    painter->drawText(0.45*pageWidth,yPosition,str);
    nextRow(yPosition);
    str="Дата от: "+QString::fromStdString(pReport->getDateFrom())+"    Дата до: "+QString::fromStdString(pReport->getDateTo());
    painter->drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    str="Тип: ";
    if((pReport->getType().first==true)&&(pReport->getType().second==false)) str+="Прибыль";
    if((pReport->getType().first==false)&&(pReport->getType().second==true)) str+="Убыток";
    if((pReport->getType().first==true)&&(pReport->getType().second==true)) str+="Все";
    painter->drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    str="Сумма от: "+ QString::number(pReport->getSumFrom())+" Сумма до: "+QString::number(pReport->getSumTo());
    painter->drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    str="Валюты: ";
    painter->drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    //stringFromVector(pReport->getCurrency())
    //printComboBoxCheckedList(pCbxCurrency,painter,yPosition);
    str="Категории: ";
    painter->drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    //stringFromVector(pReport->getCategory())
    //printComboBoxCheckedList(pCbxCategory,painter,yPosition);
    str="Описания: ";
    painter->drawText(leftBorder,yPosition,str);
    nextRow(yPosition);
    //stringFromVector(pReport->getDescription())
    //printComboBoxCheckedList(pCbxDescription,painter,yPosition);
}

void ReportPrint::printTable(double& yPosition){
    const double pageWidthWithoutBorders=(pageWidth-leftBorder-rightBorder);
    const double xType=0.15*pageWidthWithoutBorders;
    const double xCategory=0.28*pageWidthWithoutBorders;
    const double xDescription=0.54*pageWidthWithoutBorders;
    const double xSum=0.8*pageWidthWithoutBorders;
    const double xCurrency=0.92*pageWidthWithoutBorders;
    //print table header
    painter->drawText(leftBorder,yPosition,"Дата");
    painter->drawText(leftBorder+xType,yPosition,"Тип");
    painter->drawText(leftBorder+xCategory,yPosition,"Категория");
    painter->drawText(leftBorder+xDescription,yPosition,"Описание");
    painter->drawText(leftBorder+xSum,yPosition,"Сумма");
    painter->drawText(leftBorder+xCurrency,yPosition,"Валюта");
    nextRow(yPosition);
    //print table
    unsigned int rows=pReport->rowsCount();
    for(unsigned int row = 0;row<rows;++row){
        RecordString rec=pReport->getRow(row);
        painter->drawText(leftBorder,yPosition,rec.getDate().c_str());
        painter->drawText(leftBorder+xType,yPosition,rec.getType().c_str());
        painter->drawText(leftBorder+xCategory,yPosition,rec.getCategory().c_str());
        painter->drawText(leftBorder+xDescription,yPosition,rec.getDescription().c_str());
        painter->drawText(leftBorder+xSum,yPosition,QString::number(rec.getSum()));
        painter->drawText(leftBorder+xCurrency,yPosition,rec.getCurrency().c_str());
        yPosition+=leading;
        if(yPosition>(pageHeight-verticalBorder)&&(row!=(rows-1))){
            printer->newPage();
            yPosition=verticalBorder+leading;
            //print table header
            painter->drawText(leftBorder,yPosition,"Дата");
            painter->drawText(leftBorder+xType,yPosition,"Тип");
            painter->drawText(leftBorder+xCategory,yPosition,"Категория");
            painter->drawText(leftBorder+xDescription,yPosition,"Описание");
            painter->drawText(leftBorder+xSum,yPosition,"Сумма");
            painter->drawText(leftBorder+xCurrency,yPosition,"Валюта");
            yPosition+=leading;
        }
    }
}

void ReportPrint::nextRow(double& yPosition)const{
    yPosition+=leading;
    if(yPosition>(pageHeight-verticalBorder)){
        printer->newPage();
        yPosition=verticalBorder+leading;
    }
}
