TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

unix {
    LIBS += -lSDL2main -lSDL2 -lGLEW -lGL
}

win32 {
    INCLUDEPATH += C:\GLEW-MinGW\include C:\SDL2-2.0.3\i686-w64-mingw32\include
    LIBS += -lmingw32 -LC:\SDL2-2.0.3\i686-w64-mingw32\lib -lsdl2main -lsdl2 -LC:\GLEW-MinGW\lib -lglew32 -lopengl32
    DEPENDPATH += .
}

SOURCES += \
    main.cpp

HEADERS += \
    util/vec.hpp \
    util/mat.hpp \
    view/window/window.h \
    view/window/glwindow.h \
    asarone/linalg/matn.hpp \
    asarone/linalg/matnm.hpp \
    asarone/linalg/vec.hpp \
    asarone/linalg/vec2.hpp \
    asarone/linalg/vec3.hpp \
    asarone/linalg/vec4.hpp \
    asarone/linalg/vecn.hpp \
    asarone/thread/mutex.hpp \
    asarone/thread/thread.hpp \
    asarone/util/const.hpp \
    asarone/util/op.hpp \
    asarone/window/glwindow.hpp \
    asarone/window/window.hpp \
    model/land.h \
    model/tile.h \
    hextiling/hexarray.hpp \
    hextiling/hexlocator.hpp \
    linking/entity.hpp \
    linking/link.hpp \
    linking/linkin.hpp \
    linking/linkout.hpp \
    linking/linkset.hpp \
    linking/image.hpp \
    view/spectator.h \
    view/render.h \
    asarone/la/mat.hpp \
    asarone/la/matn.hpp \
    asarone/la/matnm.hpp \
    asarone/la/vec.hpp \
    asarone/la/vec2.hpp \
    asarone/la/vec3.hpp \
    asarone/la/vec4.hpp \
    asarone/la/vecn.hpp \
    asarone/gl/shader.hpp \
    asarone/gl/program.hpp \
    asarone/gl/vertexshader.hpp \
    asarone/gl/fragmentshader.hpp \
    asarone/gl/veretxbuffer.hpp \
    asarone/gl/framebuffer.hpp \
    view/renderprogram.h \
    asarone/gl/texture.hpp

OTHER_FILES += \
    ../shader/fragment.frag \
    ../shader/vertex.vert
