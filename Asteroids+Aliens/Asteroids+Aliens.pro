#-------------------------------------------------
#
# Project created by QtCreator 2013-02-27T16:59:00
#
#-------------------------------------------------

QT       += core gui

TARGET = Asteroids+Aliens
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    universe.cpp \
    obstacle.cpp \
    world.cpp \
    asteroid.cpp \
    alien.cpp \
    projectile.cpp \
    highscores.cpp \
    on_screen_object.cpp \
    ship_label.cpp \
    ship.cpp \
    universethread.cpp \
    instructionwindow.cpp
QMAKE_CXXFLAGS += -std=c++0x

HEADERS  += mainwindow.h \
    universe.h \
    obstacle.h \
    world.h \
    asteroid.h \
    alien.h \
    projectile.h \
    highscores.h \
    on_screen_object.h \
    ship_label.h \
    ship.h \
    universethread.h\
    instructionwindow.h
FORMS    += mainwindow.ui \
    instructionwindow.ui

RESOURCES += \
    Images.qrc
