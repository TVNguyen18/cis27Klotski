/**
* Program Name: KlotSki Game
* Discussion  : Vertex Shader
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#version 410

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexTexture;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;

void main() {
	vs_position = vertexPosition;
	vs_color = vertexColor;
	vs_texcoord = vec2(vertexTexture.x, vertexTexture.y*-1.0f);
	gl_Position = vec4(vertexPosition, 1.0f);	
};

