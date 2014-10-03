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

class Render : public Window::Render
{
private:
	Shader *vs, *fs;
	RenderProgram *prog;
	Texture *tex;

	fmat2 projection_matrix = unifmat2;

	double phi = 0.0;
	VertexBuffer coord, color, texcoord;

public:
	virtual void init() throw(Exception)
	{
		vs = new VertexShader();
		fs = new FragmentShader();
		prog = new RenderProgram();

		tex = new Texture();

		try
		{
			tex->loadFromFile("../texture/ghost.bmp");
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

		fvec2 coord_array[18];
		fvec3 color_array[18];
		fvec2 texcoord_array[18];

		HexLocator locator(1.0,0);
		fvec3 vertex_colors[7] = {
			fvec3(1.0,0.0,0.0),
			fvec3(1.0,1.0,0.0),
			fvec3(0.0,1.0,0.0),
			fvec3(0.0,1.0,1.0),
			fvec3(0.0,0.0,1.0),
			fvec3(1.0,0.0,1.0),
			fvec3(1.0,1.0,1.0)
		};
		fvec2 vertex_texcoords[7] = {
			fvec2(1.0,0.5),
			fvec2(0.5,1.0),
			fvec2(0.0,1.0),
			fvec2(0.0,0.5),
			fvec2(0.5,0.0),
			fvec2(1.0,0.0),
			fvec2(0.5,0.5)
		};

		for(int i = 0; i < 6; ++i)
		{
			coord_array[3*i] = locator.tile_vertex[i];
			coord_array[3*i + 1] = locator.tile_vertex[(i+1)%6];
			coord_array[3*i + 2] = nullvec2;

			color_array[3*i] = vertex_colors[6]; // vertex_colors[i];
			color_array[3*i + 1] = vertex_colors[6]; // vertex_colors[(i+1)%6];
			color_array[3*i + 2] = vertex_colors[6];

			texcoord_array[3*i] = vertex_texcoords[i];
			texcoord_array[3*i + 1] = vertex_texcoords[(i+1)%6];
			texcoord_array[3*i + 2] = vertex_texcoords[6];
		}

		coord.buffer(reinterpret_cast<const float*>(coord_array),2*18);
		color.buffer(reinterpret_cast<const float*>(color_array),3*18);
		texcoord.buffer(reinterpret_cast<const float*>(texcoord_array),2*18);

		glClearColor(0,0,0,1);
	}

	virtual void resize(const Window::Size &s)
	{
		projection_matrix(0,0) = static_cast<float>(s.h)/s.w;
	}

	virtual void display()
	{
		phi += 0.01;

		fmat2 modelview_matrix = {cos(phi),sin(phi),-sin(phi),cos(phi)};

		glClear(GL_COLOR_BUFFER_BIT);

		prog->enable();
		prog->setProjectionMatrix(projection_matrix);
		prog->setModelviewMatrix(modelview_matrix);
		prog->bindTexture(tex);
		prog->enableAttribs();

		coord.bind();
		prog->pointCoord(nullptr);
		coord.unbind();
		color.bind();
		prog->pointColor(nullptr);
		color.unbind();
		texcoord.bind();
		prog->pointTexCoord(nullptr);
		texcoord.unbind();
		glDrawArrays(GL_TRIANGLES,0,18);

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
