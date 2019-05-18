/**
* Program Name: KlotSki Game
* Discussion  : Declaration File --
*				  vertex.h
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#ifndef VERTEX_H
#define VERTEX_H

#include "include.h"

using namespace std;

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 textCoord;
};
typedef struct Vertex TVertex;
typedef struct Vertex* TVertexAddr;

void initVertexAry(Vertex myVertexAry[]);
void initCellVertexAry(Vertex cellVerticesAry[]);
void initIndices(GLuint indices[]);

void printVertexAry(Vertex myVertexAry[]);
void updateVertexAray(Vertex myVertexAry[], 
	Vertex cellVerticesAry[], int posMatrix[]);

#endif
