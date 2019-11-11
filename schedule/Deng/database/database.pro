TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

INCLUDEPATH += \
        $$PWD/libosmium_2.15.3/include/\
        $$PWD/protozero/include/

LIBS += -lz\
        -pthread

HEADERS += \
    modelDataHandler.h \
    modelDataStructure.h
