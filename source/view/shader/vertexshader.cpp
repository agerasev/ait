#include "vertexshader.h"

GLuint VertexShader::create() {
    return glCreateShader(GL_VERTEX_SHADER);
}

#include<iostream>

VertexShader::VertexShader(const char *src) : Shader(src) {
    id = create();
    compile();
}

VertexShader::~VertexShader() {
    glDeleteShader(id);
}
