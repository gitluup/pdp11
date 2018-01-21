#-------------------------------------------------
#
# Project created by QtCreator 2018-01-21T12:45:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PDP
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
        mainwindow.cpp \
        src/cpu/decoder/decoder.cpp \
        src/cpu/instruction/instruction.cpp \
        src/cpu/cpu.cpp \
        src/emulator/emulator.cpp \
        src/memory/memory.cpp \
        emulatorwindow.cpp

HEADERS += \
        emulatorwindow.h \
        src/cpu/decoder/decoder.h \
        src/cpu/instruction/instruction.h \
        src/cpu/cpu.h \
        src/emulator/emulator.h \
        src/memory/memory.h

FORMS += \
        emulatorwindow.ui

DISTFILES +=
