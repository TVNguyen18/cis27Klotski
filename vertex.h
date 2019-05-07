#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#include <glm/glm.hpp>

#include "stack.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 textCoord;
};
typedef struct Vertex TVertex;
typedef struct Vertex* TVertexAddr;

void initVertexAry(Vertex myVertexAry[]);
void initCellVertexAry(Vertex cellVerticesAry[]);
void printVertexAry(Vertex myVertexAry[]);
void updateVertexAray(Vertex myVertexAry[], Vertex cellVerticesAry[], int posMatrix[]);
#endif
