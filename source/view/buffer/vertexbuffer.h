#ifndef VBO_H
#define VBO_H

#include<GL/glew.h>

class VBO
{
private:
    GLuint id;
    GLuint length;
public:
    VBO() {
        length = 0;
        glGenBuffers(1, &id);
    }
    virtual ~VBO() {
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
    }
    GLuint size() const {
        return length;
    }
};

#endif // VBO_H
