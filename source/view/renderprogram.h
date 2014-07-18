#ifndef RENDERPROGRAM_H
#define RENDERPROGRAM_H

#include<asarone/gl/program.hpp>
#include<asarone/gl/texture.hpp>

class RenderProgram : public Program
{
private:
	GLuint aspect;
	GLuint ang;

	GLuint vertex;
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

	void setAspect(float a)
	{
		glUniform1f(aspect, a);
	}
	void setAng(float a)
	{
		glUniform1f(ang, a);
	}
	void bindTexture(const Texture *t)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(texture,0);
		t->bind();
	}

	void enableAttribs()
	{
		glEnableVertexAttribArray(vertex);
		glEnableVertexAttribArray(color);
		glEnableVertexAttribArray(texcoord);
	}
	void disableAttribs()
	{
		glDisableVertexAttribArray(vertex);
		glDisableVertexAttribArray(color);
		glDisableVertexAttribArray(texcoord);
	}
	void pointVertex(float *p)
	{
		glVertexAttribPointer(vertex, 2, GL_FLOAT, GL_FALSE, 0, p);
	}
	void pointColor(float *p)
	{
		glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, p);
	}
	void pointTexCoord(float *p)
	{
		glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 0, p);
	}

	virtual void pull()
	{
		aspect = getUniform("aspect");
		ang = getUniform("ang");
		vertex = getAttribute("vertex");
		color = getAttribute("color");
		texcoord = getAttribute("texcoord");
	}
};

#endif // RENDERPROGRAM_H
