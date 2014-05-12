#ifndef SHADER_H
#define SHADER_H

#include<GL/glew.h>

class Shader
{
private:
    GLchar *source;

    GLchar *loadSource(const char *addr);
    void log();

protected:
    GLuint id;

    virtual GLuint create() = 0;
    void compile();

public:
    Shader(const char *addr);
    virtual ~Shader();
    GLuint getID() const;
};

#endif // SHADER_H
