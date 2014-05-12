TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lSDL2 -lSDL2main -lGLEW -lGL

SOURCES += \
    main.cpp \
    map/map.cpp \
    view/renderer.cpp \
    model/map.cpp

HEADERS += \
    view/renderer.h \
    map/imap.h \
    util/vec.hpp \
    util/mat.hpp \
    model/map.h \
    model/imap.h
