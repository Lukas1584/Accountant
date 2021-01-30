#pragma once
#include <memory>
#include <QtPrintSupport>
#include <QPainter>
#include <QFont>
#include <QComboBox>
#include <QObject>
#include "SRC/BusinessLogic/Report.h"
#include "SRC/BusinessLogic/RecordString.h"

class ReportPrint:public QObject{
    Q_OBJECT
public:
    explicit ReportPrint(std::shared_ptr<Report>& report);
    ~ReportPrint();
    void printReport(const std::string& userName,const std::string& currentDate);
private slots:
    void printReport();
private:
    std::shared_ptr<Report> pReport;
    QPrinter* printer;
    QPainter* painter;
    QPrintPreviewDialog* printDialog;

    void calculatePageParameters();
    void printHeader(double& yPosition,const std::string& userName,const std::string& currentDate);
    void printTable(double& yPosition);
    void nextRow(double& yPosition)const;

    /*print settings*/
    double leading;

    const std::string font="Arial";
    const int fontSize=12;

    double pageWidth;
    double pageHeight;
    double leftBorder;
    double rightBorder;
    double verticalBorder;
};
