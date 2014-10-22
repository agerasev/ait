#ifndef RENDER_H
#define RENDER_H

#include<4u/window/glwindow.hpp>

#include<cmath>
#include<iostream>

#include<4u/la/vec.hpp>

#include<4u/util/const.hpp>

#include<4u/gl/vertexshader.hpp>
#include<4u/gl/fragmentshader.hpp>
#include<4u/gl/texture.hpp>

#include<4u/gl/vertexbuffer.hpp>

#include<4u/exception/exception.hpp>

#include"renderprogram.hpp"

#include<model/hex/hexlocator.hpp>

#include"mapview.hpp"
#include"spectator.hpp"

class Render : public Window::Render
{
private:
	Shader *vs, *fs;
	RenderProgram *prog;
	Texture *tex;

	fmat2 projection_matrix = unifmat2;

	MapView *map_view = nullptr;
	Spectator spect;

	ivec2 resolution;

public:
	Render(MapView *mv) :
		map_view(mv)
	{

	}

	virtual void init() throw(Exception)
	{
		vs = new VertexShader();
		fs = new FragmentShader();
		prog = new RenderProgram();

		tex = new Texture();

		try
		{
			tex->loadFromFile("../texture/terrian.bmp");
		}
		catch (const Exception &e)
		{
			std::cerr << e.getMessage() << std::endl;
			return;
		}


		try
		{
			vs->loadSourceFromFile("../shader/vertex.vert");
			vs->compile();
			fs->loadSourceFromFile("../shader/fragment.frag");
			fs->compile();

			prog->attach(vs);
			prog->attach(fs);
			prog->link();
			prog->pull();
		}
		catch (const Exception &e)
		{
			std::cerr << e.getMessage() << std::endl;
			return;
		}

		glClearColor(0,0,0,1);
	}

	virtual void resize(const Window::Size &s)
	{
		projection_matrix(0,0) = static_cast<float>(s.h)/s.w;
		resolution = ivec2(s.w,s.h);
	}

	virtual void display()
	{
		map_view->update();
		
		glClear(GL_COLOR_BUFFER_BIT);

		prog->enable();
		prog->setTranslation(spect.getPos());
		prog->setProjectionMatrix(projection_matrix);
		prog->setModelviewMatrix(spect.getOri());
		prog->bindTexture(tex);
		prog->enableAttribs();
		
		map_view->draw(prog,spect,projection_matrix);

		prog->disableAttribs();
		prog->disable();
	}

	virtual void dispose()
	{
		delete tex;

		prog->detach(vs);
		prog->detach(fs);
		delete prog;
		delete vs;
		delete fs;
	}

	ivec2 getResolution() const
	{
		return resolution;
	}

	Spectator &getSpectator()
	{
		return spect;
	}
};

#endif // RENDER_H
