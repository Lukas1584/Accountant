SOURCES += \
    Main.cpp \
    SRC/ApplicationBuilder.cpp \
    SRC/BusinessLogic/BalanceCalculator.cpp \
    SRC/BusinessLogic/BusinessLogic.cpp \
    SRC/BusinessLogic/RecordString.cpp \
    SRC/BusinessLogic/RecordsOperations.cpp \
    SRC/BusinessLogic/Report.cpp \
    SRC/BusinessLogic/ReportSavePdf.cpp \
    SRC/BusinessLogic/ReportSaveTxt.cpp \
    SRC/BusinessLogic/User.cpp \
    SRC/BusinessLogic/UserFileOperations.cpp \
    SRC/DataBase/Data.cpp \
    SRC/DataBase/DataOperations.cpp \
    SRC/DataBase/Record.cpp \
    SRC/GUI/ChangePasswordWidget.cpp \
    SRC/GUI/MainWindow.cpp \
    SRC/GUI/MoneyRepositaryWidget.cpp \
    SRC/GUI/PasswordWidget.cpp \
    SRC/GUI/ReportWidget.cpp \
    SRC/GUI/UserWidget.cpp

HEADERS += \
    SRC/ApplicationBuilder.h \
    SRC/BusinessLogic/AbstractBusinessLogic.h \
    SRC/BusinessLogic/BalanceCalculator.h \
    SRC/BusinessLogic/BusinessLogic.h \
    SRC/BusinessLogic/RecordString.h \
    SRC/BusinessLogic/RecordsOperations.h \
    SRC/BusinessLogic/Report.h \
    SRC/BusinessLogic/ReportSavePdf.h \
    SRC/BusinessLogic/ReportSaveTxt.h \
    SRC/BusinessLogic/User.h \
    SRC/BusinessLogic/UserFileOperations.h \
    SRC/DataBase/AbstractData.h \
    SRC/DataBase/AbstractDataFileOperations.h \
    SRC/DataBase/Data.h \
    SRC/DataBase/DataOperations.h \
    SRC/DataBase/Record.h \
    SRC/GUI/ChangePasswordWidget.h \
    SRC/GUI/MainWindow.h \
    SRC/GUI/MoneyRepositaryWidget.h \
    SRC/GUI/PasswordWidget.h \
    SRC/GUI/ReportWidget.h \
    SRC/GUI/UserWidget.h

QT += widgets
QT += core
QT += printsupport

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SRC/Libs/libharu-master/ -llibhpdf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SRC/Libs/libharu-master/ -llibhpdf
else:unix: LIBS += -L$$PWD/SRC/Libs/libharu-master/ -llibhpdf

INCLUDEPATH += $$PWD/SRC/Libs/libharu-master
DEPENDPATH += $$PWD/SRC/Libs/libharu-master
