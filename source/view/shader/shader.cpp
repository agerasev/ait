#include "shader.h"

#include<fstream>
#include<iostream>

using namespace std;

Shader::Shader(const char *addr) {
    source = loadSource(addr);
}

Shader::~Shader() {
    delete[] source;
}

GLuint Shader::getID() const {
    return id;
}

GLchar *Shader::loadSource(const char *addr) {

    int length;

    ifstream is;
    is.open (addr, ios::binary );

    is.seekg (0, ios::end);
    length = is.tellg();
    is.seekg (0, ios::beg);

    char *str;
    str = new char[length+1];
    str[length] = '\0';

    is.read(str,length);
    is.close();

    return static_cast<GLchar*>(str);
}

void Shader::compile() {
    glShaderSource(id, 1, const_cast<const GLchar**>(&source), nullptr);
    glCompileShader(id);
    log();
}

void Shader::log() {

    int   infologLen   = 0;
    int   charsWritten = 0;
    char *infoLog;

    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infologLen);

    if(infologLen > 1)
    {
        infoLog = new char[infologLen];
        glGetShaderInfoLog(id, infologLen, &charsWritten, infoLog);
        cout << infoLog;
        delete[] infoLog;
    }
}
