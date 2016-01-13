TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    game.cpp \
    system.cpp \
    triangle.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    constants.h \
    game.h \
    system.h \
    triangle.h


LIBS += -L"C:\Users\David Wu\Desktop\S.M.F.L\SFML-2.3\lib`"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window #ORDER MATTERS!
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "C:\Users\David Wu\Desktop\S.M.F.L\SFML-2.3\include"
DEPENDPATH += "C:\Users\David Wu\Desktop\S.M.F.L\SFML-2.3\include"
