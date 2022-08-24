#-------------------------------------------------
#
# Project created by QtCreator 2021-01-15T22:09:42
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nogo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainsense.cpp \
    mypushbutton.cpp \
    helpsense.cpp \
    newgamesense0.cpp \
    newgamesense1.cpp \
    achievementsense.cpp \
    loadgamesense.cpp \
    newgamesense2.cpp \
    randommaker.cpp \
    validcounter.cpp \
    aiplayer.cpp \
    gamejudge.cpp \
    nogosense.cpp

HEADERS += \
        mainsense.h \
    mypushbutton.h \
    helpsense.h \
    newgamesense0.h \
    newgamesense1.h \
    achievementsense.h \
    loadgamesense.h \
    newgamesense2.h \
    randommaker.h \
    validcounter.h \
    aiplayer.h \
    gamejudge.h \
    nogosense.h

FORMS += \
        mainsense.ui \
    achievementsense.ui \
    loadgamesense.ui \
    nogosense.ui

RESOURCES += \
    res.qrc

CONFIG +=  \
    resources_big

RC_FILE += \
    Icon.rc
