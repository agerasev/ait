#ifndef RENDER_H
#define RENDER_H

#include<asarone/window/glwindow.hpp>

#include<cmath>
#include<asarone/util/const.hpp>

#include<asarone/gl/vertexshader.hpp>
#include<asarone/gl/fragmentshader.hpp>
#include<asarone/gl/texture.hpp>

#include"renderprogram.h"

class Render : public Window::Render
{
private:
	float aspect; // aspect ratio

	Shader *vs, *fs;
	RenderProgram *prog;
	Texture *tex;

	double phi = 0.0;
	float vert[6] = {
		cos(0.0), sin(0.0),
		cos(0.66*PI), sin(0.66*PI),
		cos(1.33*PI), sin(1.33*PI)
	};
	float col[9] = {
		1,0,0,
		0,1,0,
		0,0,1
	};
	float texc[6] = {
		0, 0,
		0, 1,
		1, 0
	};

public:
	virtual int init()
	{
		vs = new VertexShader();
		fs = new FragmentShader();
		prog = new RenderProgram();

		tex = new Texture();
		tex->loadFromFile("../texture/sierpinsky-high.bmp");

		/* Need to add exceptions here */

		vs->loadSourceFromFile("../shader/vertex.vert");
		vs->compile();
		fs->loadSourceFromFile("../shader/fragment.frag");
		fs->compile();

		prog->attach(vs);
		prog->attach(fs);
		prog->link();
		prog->pull();

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glClearColor(0,0,0,1);

		return 0;
	}

	virtual void resize(const Window::Size &s)
	{
		aspect = static_cast<float>(s.h)/s.w;
	}

	virtual void display()
	{
		phi += 0.01;

		glClear(GL_COLOR_BUFFER_BIT);

		prog->enable();
		prog->setAspect(aspect);
		prog->setAng(phi);
		prog->bindTexture(tex);
		prog->enableAttribs();

		prog->pointVertex(vert);
		prog->pointColor(col);
		prog->pointTexCoord(texc);
		glDrawArrays(GL_TRIANGLES,0,3);

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
};

#endif // RENDER_H
