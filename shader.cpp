#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "shader.h"

using namespace std;

Shader::Shader(const string& filepath) 
	: mFilePath(filepath), mRendererID(0) {
	ShaderProgramSource source = parseShader(filepath);
	mRendererID = createShader(source.VertexSource, source.FragmentSource);

}

Shader::~Shader() {
	glDeleteProgram(mRendererID);
}

ShaderProgramSource Shader::parseShader(const string& filepath) {
	ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	string line;
	stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos) {
				type = ShaderType::VERTEX;
			} else {
				if (line.find("fragment") != string::npos) {
					type = ShaderType::FRAGMENT;
				}
			}
		} else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, const string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	int result;
	int length;
	char* message;
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader!" << endl
			<< message << endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::createShader(const string& vertexShader, const string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::bind() const {
	glUseProgram(mRendererID);
}

void Shader::unbind() const {
	glUseProgram(0);
}

void Shader::setUniform4F(const string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

unsigned int Shader::getUniformLocation(const string& name) {
	int location = glGetUniformLocation(mRendererID, name.c_str());

	if (mUniformLocationCache.find(name) != mUniformLocationCache.end()) {
		return mUniformLocationCache[name];
	} else {

		if (location == -1) {
			cout << "Warning: uniform '" << name << "' doesn't exist!" << endl;
		}

		return location;
	}
}