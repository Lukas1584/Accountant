#include "SRC/Application_Builder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application_Builder* app=new  Application_Builder;

    return a.exec();
}
