#ifndef VERETXBUFFER_HPP
#define VERETXBUFFER_HPP

#include<GL/glew.h>

class VertexBuffer
{
private:
	GLuint id;
	GLuint length;
public:
	VertexBuffer() {
		length = 0;
		glGenBuffers(1, &id);
	}
	virtual ~VertexBuffer() {
		unbind();
		glDeleteBuffers(1, &id);
	}
	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	void unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	template <typename T>
	void buffer(T *varr, GLuint vlen) {
		bind();
		length = vlen;
		glBufferData(GL_ARRAY_BUFFER, vlen*sizeof(T), varr, GL_STATIC_DRAW);
		unbind();
	}
	virtual void draw()
	{
		glDrawArrays(GL_TRIANGLES,0,length);
	}
	GLuint size() const {
		return length;
	}
};

#endif // VERETXBUFFER_HPP
