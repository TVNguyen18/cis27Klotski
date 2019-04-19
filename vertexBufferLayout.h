#include <vector>
#include "GL/glew.h"

using namespace std;

struct VertexBufferElement {
    unsigned int type;
	unsigned int count;
	unsigned char normalized;
};

class VertexBufferLayout {
public:
	VertexBufferLayout() : mStride(0) {

	}
	
	template<typename T>
	void push(int count) {
		static_assert(false);
	}

	template<>
	void push<float>(int count) {
		mElements.push_back({GL_FLOAT, static_cast<unsigned int>(count), GL_FALSE});
		mStride += sizeof(GLfloat);
	}

	template<>
	void push<unsigned int>(int count) {
		mElements.push_back({GL_UNSIGNED_INT, static_cast<unsigned int>(count), GL_TRUE});
		mStride += sizeof(GLuint);
	}

	template<>
	void push<unsigned char>(int count) {
		mElements.push_back({GL_UNSIGNED_BYTE, static_cast<unsigned int>(count), GL_FALSE});
		mStride += sizeof(GLbyte);
	}

	inline const vector<VertexBufferElement> getElements() const { return mElements; }
	inline unsigned int getStride() const { return mStride; }
private:
	vector<VertexBufferElement> mElements;
	unsigned int mStride;
};