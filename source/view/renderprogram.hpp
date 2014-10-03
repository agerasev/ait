#ifndef RENDERPROGRAM_H
#define RENDERPROGRAM_H

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>

#include<4u/gl/program.hpp>
#include<4u/gl/texture.hpp>

class RenderProgram : public Program
{
private:
	GLuint model_matrix;
	GLuint view_matrix;
	GLuint texsize;

	GLuint coord;
	GLuint color;
	GLuint texcoord;

	GLuint texture;

public:
	RenderProgram() : Program()
	{

	}
	virtual ~RenderProgram()
	{

	}

	void setProjectionMatrix(const fmat2 &m)
	{
		glUniformMatrix2fv(model_matrix, 1, GL_FALSE, m.data);
	}
	void setModelviewMatrix(const fmat2 &m)
	{
		glUniformMatrix2fv(view_matrix, 1, GL_FALSE, m.data);
	}

	void bindTexture(const Texture *t)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(texture,0);
		t->bind();
	}

	void enableAttribs()
	{
		glEnableVertexAttribArray(coord);
		glEnableVertexAttribArray(color);
		glEnableVertexAttribArray(texcoord);
	}
	void disableAttribs()
	{
		glDisableVertexAttribArray(coord);
		glDisableVertexAttribArray(color);
		glDisableVertexAttribArray(texcoord);
	}
	void pointCoord(const float *p = nullptr)
	{
		glVertexAttribPointer(coord, 2, GL_FLOAT, GL_FALSE, 0, p);
	}
	void pointColor(const float *p = nullptr)
	{
		glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, p);
	}
	void pointTexCoord(const float *p = nullptr)
	{
		glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 0, p);
	}

	virtual void pull()
	{
		model_matrix = getUniform("model");
		view_matrix = getUniform("view");

		coord = getAttribute("coord");
		color = getAttribute("color");
		texcoord = getAttribute("texcoord");
	}
};

#endif // RENDERPROGRAM_H
