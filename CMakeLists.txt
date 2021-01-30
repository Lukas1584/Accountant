cmake_minimum_required(VERSION 3.5)

project(Accountant LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}PrintSupport REQUIRED)

add_executable(Accountant
      main.cpp
      SRC/ApplicationBuilder.cpp

      SRC/DataBase/Data.cpp
      SRC/DataBase/DataOperations.cpp
      SRC/DataBase/Record.cpp

      SRC/GUI/MainWindow.cpp
      SRC/GUI/ChangePasswordWidget.cpp
      SRC/GUI/GraphicWidget.cpp
      SRC/GUI/MoneyRepositaryWidget.cpp
      SRC/GUI/PasswordWidget.cpp
      SRC/GUI/ReportWidget.cpp
      SRC/GUI/UserWidget.cpp

      SRC/BusinessLogic/BusinessLogic.cpp
      SRC/BusinessLogic/BalanceCalculator.cpp
      SRC/BusinessLogic/GraphicBuilder.cpp
      SRC/BusinessLogic/RecordsOperations.cpp
      SRC/BusinessLogic/RecordString.cpp
      SRC/BusinessLogic/Report.cpp
      SRC/BusinessLogic/ReportSaveTxt.cpp
      SRC/BusinessLogic/UserFileOperations.cpp
      SRC/BusinessLogic/ReportSaveTxt.cpp
      SRC/BusinessLogic/ReportPrint.cpp
      SRC/BusinessLogic/GraphicBuilder.cpp
      SRC/BusinessLogic/User.cpp
  )

target_link_libraries(Accountant PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

