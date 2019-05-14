#ifndef SHADER_H
#define SHADER_H

#include "include.h"

string readShaderSource(string fileName);
bool compileShader(GLuint shaderID);


#endif