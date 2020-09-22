SOURCES += \
    Main.cpp \
    SRC/Application_Builder.cpp \
    SRC/BusinessLogic/Balance_Calculator.cpp \
    SRC/BusinessLogic/BusinessLogic.cpp \
    SRC/BusinessLogic/Record_String.cpp \
    SRC/BusinessLogic/Records_Operations.cpp \
    SRC/BusinessLogic/Report.cpp \
    SRC/BusinessLogic/Report_Save.cpp \
    SRC/BusinessLogic/User.cpp \
    SRC/BusinessLogic/User_File_Operations.cpp \
    SRC/DataBase/Data.cpp \
    SRC/DataBase/DataOperations.cpp \
    SRC/DataBase/Record.cpp \
    SRC/GUI/Change_Password_Widget.cpp \
    SRC/GUI/Main_Window.cpp \
    SRC/GUI/Money_Repositary_Widget.cpp \
    SRC/GUI/Password_Widget.cpp \
    SRC/GUI/Planning_Widget.cpp \
    SRC/GUI/Report_Widget.cpp \
    SRC/GUI/User_Widget.cpp

HEADERS += \
    SRC/Application_Builder.h \
    SRC/BusinessLogic/AbstractBusinessLogic.h \
    SRC/BusinessLogic/Balance_Calculator.h \
    SRC/BusinessLogic/BusinessLogic.h \
    SRC/BusinessLogic/Record_String.h \
    SRC/BusinessLogic/Records_Operations.h \
    SRC/BusinessLogic/Report.h \
    SRC/BusinessLogic/Report_Save.h \
    SRC/BusinessLogic/User.h \
    SRC/BusinessLogic/User_File_Operations.h \
    SRC/DataBase/AbstractData.h \
    SRC/DataBase/AbstractDataFileOperations.h \
    SRC/DataBase/Data.h \
    SRC/DataBase/DataOperations.h \
    SRC/DataBase/Record.h \
    SRC/GUI/Change_Password_Widget.h \
    SRC/GUI/Main_Window.h \
    SRC/GUI/Money_Repositary_Widget.h \
    SRC/GUI/Password_Widget.h \
    SRC/GUI/Planning_Widget.h \
    SRC/GUI/Report_Widget.h \
    SRC/GUI/User_Widget.h

QT += widgets
QT += core
QT += printsupport

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SRC/Libs/libharu-master/ -llibhpdf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SRC/Libs/libharu-master/ -llibhpdf
else:unix: LIBS += -L$$PWD/SRC/Libs/libharu-master/ -llibhpdf

INCLUDEPATH += $$PWD/SRC/Libs/libharu-master
DEPENDPATH += $$PWD/SRC/Libs/libharu-master

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SRC/Libs/libharu-master/ -llibhpdfs
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SRC/Libs/libharu-master/ -llibhpdfs
else:unix: LIBS += -L$$PWD/SRC/Libs/libharu-master/ -llibhpdfs

INCLUDEPATH += $$PWD/SRC/Libs/libharu-master
DEPENDPATH += $$PWD/SRC/Libs/libharu-master
