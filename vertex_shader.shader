#version 410

in vec3 vertex;

out vec3 vertexColor;
out vec2 vertexCoord;

void main() {
	gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0);
	vertexColor = vec3(1.0, 1.0, 0.0);
	vertexCoord = vec2(vertex.x, vertex.y);
};

