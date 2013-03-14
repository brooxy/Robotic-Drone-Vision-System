#-------------------------------------------------
#
# Project created by QtCreator 2013-02-14T13:03:32
#
#-------------------------------------------------

QT       += core gui

TARGET = VisionAssignment
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += /usr/local/include/

LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_highgui \
-lopencv_imgproc \
-lopencv_features2d \
-lopencv_objdetect

SOURCES += main.cpp
