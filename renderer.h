#pragma once

#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

class Renderer {
public:
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};