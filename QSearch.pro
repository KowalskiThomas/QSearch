#-------------------------------------------------
#
# Project created by QtCreator 2019-07-15T10:17:13
#
#-------------------------------------------------

debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}

CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
}
CONFIG(release, debug|release) {
    CONFIG -= debug release
    CONFIG += release
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSearch
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        configuration.cpp \
        fileinfowidget.cpp \
        filesearcher.cpp \
        filterconverter.cpp \
        main.cpp \
        mainwindow.cpp \
        resultsmodel.cpp \
        resultstableview.cpp \
        task.cpp \
        utils.cpp

HEADERS += \
        configuration.h \
        fileinfowidget.h \
        filesearcher.h \
        filterconverter.h \
        mainwindow.h \
        resultsmodel.h \
        resultstableview.h \
        task.h \
        utils.h

FORMS += \
        fileinfowidget.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

debug {
    message("Building for debug")
    QMAKE_CXXFLAGS -= -O
    QMAKE_CXXFLAGS -= -O1
    QMAKE_CXXFLAGS -= -O3
    QMAKE_CXXFLAGS -= -O2
    QMAKE_CXXFLAGS *= -O0
}

release | profile {
    QMAKE_CXXFLAGS -= -O
    QMAKE_CXXFLAGS -= -O1
    QMAKE_CXXFLAGS -= -O2
    QMAKE_CXXFLAGS *= -O3
}

profile {
    message("Building for profiling")
}

release {
    message("Building for release")
    DEFINES += QT_NO_DEBUG_OUTPUT=1
    DEFINES += QT_NO_WARNING_OUTPUT=1
    DEFINES += QT_NO_INFO_OUTPUT=1
}

