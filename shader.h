#pragma once

#include <string>
#include <unordered_map>
using namespace std;

struct ShaderProgramSource {
	string VertexSource;
	string FragmentSource;
};

class Shader {
public:
	Shader(const string& filename);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform4F(const string& name, float v0, float v1, float v2, float v3);
private:
	string mFilePath;
	unordered_map<string, int> mUniformLocationCache;
	unsigned int mRendererID;
	unsigned int getUniformLocation(const string& name);
	ShaderProgramSource parseShader(const string& filePath);
	unsigned int createShader(const string& vertexShader, const string& fragmentShader);
	unsigned int compileShader(unsigned int type, const string& source);
};
