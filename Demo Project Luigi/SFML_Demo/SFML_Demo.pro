TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11


SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

#LIBS += -L"..\..\SFML-2.3.2\lib"
LIBS += -L"C:\Users\David Wu\Desktop\Programming\S.M.F.L\SFML-2.3.2\lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window #ORDER MATTERS!
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

#INCLUDEPATH += "..\..\SFML-2.3.2\include"
#DEPENDPATH += "..\..\SFML-2.3.2\include"
INCLUDEPATH += "C:\Users\David Wu\Desktop\Programming\S.M.F.L\SFML-2.3.2\include"
DEPENDPATH += "C:\Users\David Wu\Desktop\Programming\S.M.F.L\SFML-2.3.2\include"
