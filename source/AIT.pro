TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lSDL2 -lSDL2main -lGLEW -lGL

SOURCES += \
    main.cpp \
    view/renderer.cpp \
    model/map.cpp \
    view/window.cpp \
    view/glwindow.cpp \
    view/shader/vertexshader.cpp \
    view/shader/shader.cpp \
    view/shader/program.cpp \
    view/shader/fragmentshader.cpp \
    view/window/window.cpp \
    view/window/glwindow.cpp \
    view/buffer/framebuffer.cpp \
    view/buffer/vertexbuffer.cpp

HEADERS += \
    view/renderer.h \
    util/vec.hpp \
    util/mat.hpp \
    model/map.h \
    model/imap.h \
    view/window.h \
    view/glwindow.h \
    view/shader/vertexshader.h \
    view/shader/shader.h \
    view/shader/program.h \
    view/shader/fragmentshader.h \
    view/window/window.h \
    view/window/glwindow.h \
    view/buffer/framebuffer.h \
    view/buffer/vertexbuffer.h
