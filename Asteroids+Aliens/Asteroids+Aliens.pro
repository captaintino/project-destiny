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
    ship.cpp \
    asteroid.cpp \
    alien.cpp \
    projectile.cpp \
    highscores.cpp

HEADERS  += mainwindow.h \
    universe.h \
    obstacle.h \
    world.h \
    ship.h \
    asteroid.h \
    alien.h \
    projectile.h \
    highscores.h

FORMS    += mainwindow.ui

RESOURCES += \
    Images.qrc
