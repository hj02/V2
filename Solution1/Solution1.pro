#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T20:38:43
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT       += core sql

TARGET = Solution1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    consoleui.cpp \
    scienceservice.cpp \
    scientist.cpp \
    sqlcomputer.cpp \
    sqlscientist.cpp \
    computer.cpp

HEADERS += \
    consoleui.h \
    menus.h \
    scienceservice.h \
    scientist.h \
    sqlcomputer.h \
    sqlscientist.h \
    computer.h
