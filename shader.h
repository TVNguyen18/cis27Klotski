/**
* Program Name: KlotSki Game
* Discussion  : Declaration File --
*				  shader.h
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#ifndef SHADER_H
#define SHADER_H

#include "include.h"

string readShaderSource(string fileName);
bool compileShader(GLuint shaderID);

#endif