#ifndef PROGRAM_H
#define PROGRAM_H

#include"shader.h"

class Program
{
private:
    GLuint id = 0;

    void logLink();
    void logAttribute(GLint attrib, const GLchar *name);
    void logUniform(GLint unif, const GLchar *name);

public:
    Program();
    virtual ~Program();

    void attach(Shader &sh);
    void link();

    virtual void enable();
    virtual void disable();

    GLint getAttribute(const GLchar *name);
    GLint getUniform(const GLchar *name);

    void enableAttribute(GLuint attrib) {
        glEnableVertexAttribArray(attrib);
    }
    void disableAttribute(GLuint attrib) {
        glDisableVertexAttribArray(attrib);
    }
};

#endif // PROGRAM_H
