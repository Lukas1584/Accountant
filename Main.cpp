#include "SRC/ApplicationBuilder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationBuilder* app=new  ApplicationBuilder;
    Q_UNUSED(app);
    return a.exec();
}
