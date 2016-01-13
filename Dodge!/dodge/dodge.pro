TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game.cpp \
    player.cpp \
    enemy.cpp \
    entity.cpp

include(deployment.pri)
qtcAddDeployment()

LIBS += -L"..\..\SFML-2.3.2\lib"
LIBS += -L"..\..\SFML-2.3.2\bin"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window #ORDER MATTERS!
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "..\..\SFML-2.3.2\include"
DEPENDPATH += "..\..\SFML-2.3.2\include"

HEADERS += \
    game.h \
    player.h \
    enemy.h \
    entity.h
