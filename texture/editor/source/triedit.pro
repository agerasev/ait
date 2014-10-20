TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lSDL2 -lSDL2main -lGL -lGLEW -lSDL_image

SOURCES += \
    main.cpp \
    window.cpp \
    glwindow.cpp \
    editor.cpp

HEADERS += \
    api.hpp \
    editor.hpp \
    glwindow.hpp \
    window.hpp
