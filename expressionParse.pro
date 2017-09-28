QT += core gui widgets qml

CONFIG += c++11

TARGET = expressionParse

TEMPLATE = app

SOURCES += main.cpp \
    expressionparse.cpp \
    elementreadfactory.cpp \
    numbertypereader.cpp \
    stringtypereader.cpp \
    variabletypereader.cpp \
    operatortypereader.cpp \
    splitortypereader.cpp \
    functiontypereader.cpp \
    element.cpp \
    datetypereader.cpp \
    mainframe.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    expressionparse.h \
    elementreadfactory.h \
    numbertypereader.h \
    stringtypereader.h \
    variabletypereader.h \
    operatortypereader.h \
    splitortypereader.h \
    functiontypereader.h \
    element.h \
    datetypereader.h \
    mainframe.h
