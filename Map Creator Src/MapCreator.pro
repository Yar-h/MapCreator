#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T14:20:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mapview.cpp \
    ruler.cpp \
    geosystemconverter.cpp

HEADERS  += mainwindow.h \
    mapview.h \
    ruler.h \
    geosystemconverter.h

FORMS    += mainwindow.ui

DISTFILES += \
    file.rc

RESOURCES +=
RC_FILE = file.rc
