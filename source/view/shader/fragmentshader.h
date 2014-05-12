#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H

#include<GL/glew.h>
#include"shader.h"

class FragmentShader : public Shader
{
protected:
    virtual GLuint create();

public:
    FragmentShader(const char *src);
    virtual ~FragmentShader();
};

#endif // FRAGMENTSHADER_H
