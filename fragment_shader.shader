#version 410

in vec3 vertexColor;
in vec2 vertexCoord;

out vec4 pixelColor;

uniform vec4 my_Color;
uniform sampler2D texture0;

void main() {
	pixelColor = my_Color;
	//pixelColor = texture(texture0, vertexCoord);
}