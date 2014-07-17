#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include<GL/glew.h>
#include"shader.h"

class VertexShader : public Shader
{
protected:
    virtual GLuint create();

public:
    VertexShader(const char *src);
    virtual ~VertexShader();
};

#endif // VERTEXSHADER_H
