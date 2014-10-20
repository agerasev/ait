#ifndef RENDERPROGRAM_H
#define RENDERPROGRAM_H

#include<4u/la/vec.hpp>
#include<4u/la/mat.hpp>

#include<4u/gl/program.hpp>
#include<4u/gl/texture.hpp>

#include<4u/gl/vertexbuffer.hpp>

class RenderProgram : public Program
{
private:
	GLuint projection_matrix;
	GLuint modelview_matrix;
	GLuint translation;
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
		glUniformMatrix2fv(projection_matrix, 1, GL_FALSE, m.data);
	}
	void setModelviewMatrix(const fmat2 &m)
	{
		glUniformMatrix2fv(modelview_matrix, 1, GL_FALSE, m.data);
	}
	void setTranslation(const fvec2 &m)
	{
		glUniform2fv(translation, 1, m.data);
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
	void pointCoord(VertexBuffer &buf)
	{
		buf.bind();
		pointCoord(nullptr);
		buf.unbind();
	}
	void pointColor(const float *p = nullptr)
	{
		glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, p);
	}
	void pointColor(VertexBuffer &buf)
	{
		buf.bind();
		pointColor(nullptr);
		buf.unbind();
	}
	void pointTexCoord(const float *p = nullptr)
	{
		glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 0, p);
	}
	void pointTexCoord(VertexBuffer &buf)
	{
		buf.bind();
		pointTexCoord(nullptr);
		buf.unbind();
	}

	virtual void pull()
	{
		modelview_matrix = getUniform("modelview");
		projection_matrix = getUniform("projection");
		translation = getUniform("translation");

		coord = getAttribute("coord");
		color = getAttribute("color");
		texcoord = getAttribute("texcoord");
	}
};

#endif // RENDERPROGRAM_H
