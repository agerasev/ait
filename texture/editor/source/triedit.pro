TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lSDL2 -lSDL_image -lGL -lGLEW -lpng

SOURCES += \
    main.cpp \
    window.cpp \
    glwindow.cpp

HEADERS += \
    api.hpp \
    editor.hpp \
    glwindow.hpp \
    window.hpp \
    png.hpp
