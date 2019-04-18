#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "vertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	glGenBuffers(1, &mRendererID);
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &mRendererID);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
