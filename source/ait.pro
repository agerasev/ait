TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

unix {
    LIBS += -lSDL2main -lSDL2 -lGLEW -lGL
}

win32 {
    INCLUDEPATH += H:\devel\local\include
    LIBS += -lmingw32 -LH:\devel\local\lib -lsdl2main -lsdl2 -lglew32 -lopengl32
}

SOURCES += \
	main.cpp

HEADERS += \
	4u/complex/complex.hpp \
	4u/complex/quaternion.hpp \
	4u/exception/compilationexception.hpp \
	4u/exception/exception.hpp \
	4u/exception/filenotfoundexception.hpp \
	4u/exception/glexception.hpp \
	4u/exception/linkageexception.hpp \
	4u/gl/fragmentshader.hpp \
	4u/gl/framebuffer.hpp \
	4u/gl/program.hpp \
	4u/gl/shader.hpp \
	4u/gl/texture.hpp \
	4u/gl/vertexbuffer.hpp \
	4u/gl/vertexshader.hpp \
	4u/la/mat.hpp \
	4u/la/matn.hpp \
	4u/la/matnm.hpp \
	4u/la/vec.hpp \
	4u/la/vec2.hpp \
	4u/la/vec3.hpp \
	4u/la/vec4.hpp \
	4u/la/vecn.hpp \
	4u/random/contrand.hpp \
	4u/random/diskrand.hpp \
	4u/random/rand.hpp \
	4u/random/sphericrand.hpp \
	4u/thread/mutex.hpp \
	4u/thread/thread.hpp \
	4u/thread/threadlocalstorage.hpp \
	4u/util/const.hpp \
	4u/util/op.hpp \
	4u/window/event.hpp \
	4u/window/glwindow.hpp \
	4u/window/glxwindow.hpp \
	4u/window/sdlwindow.hpp \
	4u/window/window.hpp \
	model/hex/hexarray.hpp \
	model/hex/hexlocator.hpp \
	model/tile.hpp \
	view/render.hpp \
	view/renderprogram.hpp \
	view/spectator.hpp \
	model/map.hpp \
	model/region.hpp \
	view/mapview.hpp \
	view/regionview.hpp \
	view/input.hpp \
	model/generator/generator.hpp \
	model/generator/landscape.hpp \
	model/config.hpp \
	view/config.hpp \
	view/textures.hpp \
	model/generator/config.hpp \
	view/entity/entityview.hpp

OTHER_FILES += \
    ../shader/fragment.frag \
    ../shader/vertex.vert \
    TODO.md
