#include "fragmentshader.h"

GLuint FragmentShader::create() {
    return glCreateShader(GL_FRAGMENT_SHADER);
}

FragmentShader::FragmentShader(const char *src) : Shader(src) {
    id = create();
    compile();
}

FragmentShader::~FragmentShader() {
    glDeleteShader(id);
}
