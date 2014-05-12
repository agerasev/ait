#include "program.h"

#include<iostream>

using namespace std;

void Program::logLink() {
    int link_ok;
    glGetProgramiv(id, GL_LINK_STATUS, &link_ok);
    if(!link_ok) {
        cout << "Error attach shaders" << endl;
    }
}
void Program::logAttribute(GLint attrib, const GLchar *name) {
    if(attrib == -1)
    {
        cout << "Could not bind attribute " << name << endl;
    }
}
void Program::logUniform(GLint unif, const GLchar *name) {
    if(unif == -1)
    {
        cout << "Could not bind uniform " << name << endl;
    }
}

Program::Program() {
    id = glCreateProgram();
}
Program::~Program() {
    glDeleteProgram(id);
}

void Program::attach(Shader &sh) {
    glAttachShader(id,sh.getID());

}
void Program::link() {
    glLinkProgram(id);
    logLink();
}

void Program::enable() {
    glUseProgram(id);
}
void Program::disable() {
    glUseProgram(0);
}

GLint Program::getAttribute(const GLchar *name) {
    GLint attrib = glGetAttribLocation(id, name);
    logAttribute(attrib,name);
    return attrib;
}
GLint Program::getUniform(const GLchar *name) {
    GLint unif = glGetUniformLocation(id, name);
    logUniform(unif,name);
    return unif;
}
