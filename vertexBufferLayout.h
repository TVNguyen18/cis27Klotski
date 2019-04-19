#pragma once

#include <vector>
#include "GL/glew.h"

using namespace std;

struct VertexBufferElement {
    unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned getSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}

		return 0;
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout() : mStride(0) {

	}
	
	template<typename T>
	void push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count) {
		mElements.push_back({GL_FLOAT, count, GL_FALSE});
		mStride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count) {
		mElements.push_back({GL_UNSIGNED_INT, count, GL_TRUE});
		mStride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count) {
		mElements.push_back({GL_UNSIGNED_BYTE, count, GL_FALSE});
		mStride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const vector<VertexBufferElement> getElements() const { return mElements; }
	inline unsigned int getStride() const { return mStride; }
private:
	vector<VertexBufferElement> mElements;
	unsigned int mStride;
};