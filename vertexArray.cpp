#include "vertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &mRendererID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &mRendererID);
}

void VertexArray::addBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout) {
	unsigned int i;
	unsigned int offset = 0;

	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	for (i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, 
			layout.getStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
} 

void VertexArray::bind() const {
	glBindVertexArray(mRendererID);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}