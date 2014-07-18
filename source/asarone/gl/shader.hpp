#ifndef SHADER_HPP
#define SHADER_HPP

#include<GL/glew.h>
#include<iostream>
#include<fstream>

class Shader
{
private:

	GLuint id;

	void logCompilation()
	{
		int   infologLen   = 0;
		int   charsWritten = 0;
		char *infoLog;

		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infologLen);

		if(infologLen > 1)
		{
			infoLog = new char[infologLen];
			glGetShaderInfoLog(id, infologLen, &charsWritten, infoLog);
			std::cout << infoLog << std::endl;
			delete[] infoLog;
		}
	}

public:

	Shader(GLenum type)
	{
		id = glCreateShader(type);
	}

	virtual ~Shader()
	{
		glDeleteShader(id);
	}

	bool loadSourceFromFile(const char *addr) {

		int length;

		std::ifstream is;
		is.open(addr, std::ios::binary);
		if(!is)
		{
			std::cout << "couldn't find " << addr << "file\n";
			return false;
		}

		is.seekg (0, std::ios::end);
		length = is.tellg();
		is.seekg (0, std::ios::beg);

		char *src;
		src = new char[length+1];
		src[length] = '\0';

		is.read(src,length);
		is.close();

		glShaderSource(id, 1, const_cast<const GLchar**>(&src), nullptr);
		return true;
	}

	bool compile()
	{
		glCompileShader(id);
		logCompilation();

		GLint st;
		glGetShaderiv(id,GL_COMPILE_STATUS,&st);
		return st==GL_TRUE?true:false;
	}

	GLuint getID() const
	{
		return id;
	}
};

#endif // SHADER_HPP
