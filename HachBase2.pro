#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T16:29:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HachBase2
TEMPLATE = app


SOURCES += \
    Singleton.cpp \
    WinMenu.cpp \
    Lang.cpp \
    BaseWidget.cpp \
    UIContext.cpp \
    UIState.cpp \
    UIStates.cpp \
    Main.cpp \
    WinHome.cpp \
    MainWidget.cpp \
    Settings.cpp

HEADERS  += \
    Singleton.hpp \
    WinMenu.hpp \
    Lang.hpp \
    BaseWidget.hpp \
    UIContext.hpp \
    UIState.hpp \
    UIStates.hpp \
    WinHome.hpp \
    MainWidget.hpp \
    Settings.hpp

FORMS    += \
    WinMenu.ui \
    WinHome.ui \
    MainWidget.ui
