#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include"shader.hpp"
#include<iostream>

class Program
{
private:
	GLuint id;

	bool logLinking() {
		int link_ok;
		glGetProgramiv(id, GL_LINK_STATUS, &link_ok);
		if(!link_ok) {
			std::cout << "Error attach shaders" << std::endl;
			return false;
		}
		return true;
	}

	void logAttribute(GLint attrib, const GLchar *name) {
		if(attrib == -1)
		{
			std::cout << "Could not bind attribute " << name << std::endl;
		}
	}
	void logUniform(GLint unif, const GLchar *name) {
		if(unif == -1)
		{
			std::cout << "Could not bind uniform " << name << std::endl;
		}
	}

public:

	Program() {
		id = glCreateProgram();
	}
	virtual ~Program() {
		glDeleteProgram(id);
	}

	void attach(const Shader *sh) {
		glAttachShader(id,sh->getID());
	}
	void detach(const Shader *sh) {
		glDetachShader(id,sh->getID());
	}
	bool link() {
		glLinkProgram(id);
		return logLinking();
	}

	void enable() {
		glUseProgram(id);
	}
	void disable() {
		glUseProgram(0);
	}

	virtual void pull() {

	}

	GLint getAttribute(const GLchar *name) {
		GLint attrib = glGetAttribLocation(id, name);
		logAttribute(attrib,name);
		return attrib;
	}
	GLint getUniform(const GLchar *name) {
		GLint unif = glGetUniformLocation(id, name);
		logUniform(unif,name);
		return unif;
	}
};

#endif // PROGRAM_HPP
