#-------------------------------------------------
#
# Project created by QtCreator 2019-09-11T19:19:41
#
#-------------------------------------------------

QT       += core gui printsupport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = miniphotoshop
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


SOURCES += \
    brightnessslider.cpp \
    logtransformdialog.cpp \
        main.cpp \
        mainwindow.cpp \
    image.cpp \
    translate_dialog.cpp \
    power_transform_dialog.cpp \
    graylevel_slicing_dialog.cpp \
    contrast_stretching_dialog.cpp \
    canny_dialog.cpp

HEADERS += \
    brightnessslider.h \
    logtransformdialog.h \
        mainwindow.h \
    image.h \
    translate_dialog.h \
    power_transform_dialog.h \
    graylevel_slicing_dialog.h \
    contrast_stretching_dialog.h \
    canny_dialog.h

FORMS += \
        brightnessslider.ui \
    logtransformdialog.ui \
        mainwindow.ui \
    translate_dialog.ui \
    power_transform_dialog.ui \
    graylevel_slicing_dialog.ui \
    contrast_stretching_dialog.ui \
    canny_dialog.ui

RESOURCES += \
    resources.qrc
