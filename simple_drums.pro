TEMPLATE = app
TARGET = simple_drums
INCLUDEPATH += .

QT += multimedia
QT += widgets

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -Iqtgamepad/include
LIBS += -Lqtgamepad/lib -lQt5Gamepad

# Input
HEADERS += sound.h drums.h
SOURCES += sound.cpp drums.cpp test.cpp
