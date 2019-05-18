/**
* Program Name: KlotSki Game
* Discussion  : vertex.cpp
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#include "vertex.h"

using namespace std;

void initVertexAry(Vertex myVertexAry[])
{
	// obj 0
	myVertexAry[0] =
	{ glm::vec3(-0.131f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[1] =
	{ glm::vec3(-0.131f, 0.175f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[2] =
	{ glm::vec3(0.119f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[3] =
	{ glm::vec3(0.119f, 0.175f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 1
	myVertexAry[4] =
	{ glm::vec3(0.125f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[5] =
	{ glm::vec3(0.125f, 0.175f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[6] =
	{ glm::vec3(0.625f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[7] =
	{ glm::vec3(0.625f, 0.175f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 2
	myVertexAry[8] =
	{ glm::vec3(0.631f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[9] =
	{ glm::vec3(0.631f, 0.175f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[10] =
	{ glm::vec3(0.881f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[11] =
	{ glm::vec3(0.881f, 0.175f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 3
	myVertexAry[12] =
	{ glm::vec3(-0.131f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[13] =
	{ glm::vec3(-0.131f, -0.5f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[14] =
	{ glm::vec3(0.119f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[15] =
	{ glm::vec3(0.119f, -0.5f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 4
	myVertexAry[16] =
	{ glm::vec3(0.125f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[17] =
	{ glm::vec3(0.125f, -0.167f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[18] =
	{ glm::vec3(0.625f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[19] =
	{ glm::vec3(0.625f, -0.167f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 5
	myVertexAry[20] =
	{ glm::vec3(0.631f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[21] =
	{ glm::vec3(0.631f, -0.5f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[22] =
	{ glm::vec3(0.881f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[23] =
	{ glm::vec3(0.881f, -0.5f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 6
	myVertexAry[24] =
	{ glm::vec3(0.128f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[25] =
	{ glm::vec3(0.128f, -0.5f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[26] =
	{ glm::vec3(0.372f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[27] =
	{ glm::vec3(0.372f, -0.5f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 7
	myVertexAry[28] =
	{ glm::vec3(0.378f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[29] =
	{ glm::vec3(0.378f, -0.5f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[30] =
	{ glm::vec3(0.622f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[31] =
	{ glm::vec3(0.622f, -0.5f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 8
	myVertexAry[32] =
	{ glm::vec3(-0.128f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[33] =
	{ glm::vec3(-0.128f, -0.838f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[34] =
	{ glm::vec3(0.116f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[35] =
	{ glm::vec3(0.116f, -0.838f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 9
	myVertexAry[36] =
	{ glm::vec3(0.634f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[37] =
	{ glm::vec3(0.634f, -0.838f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[38] =
	{ glm::vec3(0.878f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[39] =
	{ glm::vec3(0.878f, -0.838f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 10
	myVertexAry[40] =
	{ glm::vec3(-0.225f, 0.958f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[41] =
	{ glm::vec3(-0.225f, 0.833f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[42] =
	{ glm::vec3(0.975f, 0.958f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[43] =
	{ glm::vec3(0.975f, 0.833f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 11
	myVertexAry[44] =
	{ glm::vec3(-0.225f, 0.833f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[45] =
	{ glm::vec3(-0.225f, -0.833f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[46] =
	{ glm::vec3(-0.131f, 0.833f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[47] =
	{ glm::vec3(-0.131f, -0.833f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 12
	myVertexAry[48] =
	{ glm::vec3(0.881f, 0.833f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[49] =
	{ glm::vec3(0.881f, -0.833f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[50] =
	{ glm::vec3(0.975f, 0.833f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[51] =
	{ glm::vec3(0.975f, -0.833f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 13
	myVertexAry[52] =
	{ glm::vec3(-0.225f, -0.833f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[53] =
	{ glm::vec3(-0.225f, -0.958f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[54] =
	{ glm::vec3(0.119f, -0.833f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[55] =
	{ glm::vec3(0.119f, -0.958f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 14
	myVertexAry[56] =
	{ glm::vec3(0.634f, -0.833f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[57] =
	{ glm::vec3(0.634f, -0.958f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[58] =
	{ glm::vec3(0.975f, -0.833f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[59] =
	{ glm::vec3(0.975f, -0.958f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 15 - Logo
	myVertexAry[60] =
	{ glm::vec3(-0.891f, 0.833f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[61] =
	{ glm::vec3(-0.891f, 0.333f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[62] =
	{ glm::vec3(-0.328f, 0.833f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[63] =
	{ glm::vec3(-0.328f, 0.333f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 16 - Undo
	myVertexAry[64] =
	{ glm::vec3(-0.859f, -0.021f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[65] =
	{ glm::vec3(-0.859f, -0.271f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[66] =
	{ glm::vec3(-0.359f, -0.021f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[67] =
	{ glm::vec3(-0.359f, -0.271f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 17 - Reset
	myVertexAry[68] =
	{ glm::vec3(-0.859f, -0.333f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[69] =
	{ glm::vec3(-0.859f, -0.583f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[70] =
	{ glm::vec3(-0.359f, -0.333f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[71] =
	{ glm::vec3(-0.359f, -0.583f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 18 - Exit
	myVertexAry[72] =
	{ glm::vec3(-0.859f, -0.646f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[73] =
	{ glm::vec3(-0.859f, -0.896f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[74] =
	{ glm::vec3(-0.359f, -0.646f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[75] =
	{ glm::vec3(-0.359f, -0.896f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 20 - show solution
	myVertexAry[76] =
	{ glm::vec3(-0.859f, 0.292f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[77] =
	{ glm::vec3(-0.859f, 0.042f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[78] =
	{ glm::vec3(-0.359f, 0.292f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[79] =
	{ glm::vec3(-0.359f, 0.042f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
	// obj 19 - exit window
	myVertexAry[80] =
	{ glm::vec3(-0.975f, 0.958f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f) };
	myVertexAry[81] =
	{ glm::vec3(-0.975f, -0.958f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f) };
	myVertexAry[82] =
	{ glm::vec3(0.975f, 0.958f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f) };
	myVertexAry[83] =
	{ glm::vec3(0.975f, -0.958f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f) };
}

void initCellVertexAry(Vertex cellVertexAry[])
{
	// cell 0
	cellVertexAry[0] =
	{ glm::vec3(-0.131f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[1] =
	{ glm::vec3(-0.131f, 0.508f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[2] =
	{ glm::vec3(0.119f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[3] =
	{ glm::vec3(0.119f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 1
	cellVertexAry[4] =
	{ glm::vec3(0.125f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[5] =
	{ glm::vec3(0.125f, 0.508f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[6] =
	{ glm::vec3(0.375f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[7] =
	{ glm::vec3(0.375f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 2
	cellVertexAry[8] =
	{ glm::vec3(0.378f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[9] =
	{ glm::vec3(0.378f, 0.508f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[10] =
	{ glm::vec3(0.622f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[11] =
	{ glm::vec3(0.622f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 3
	cellVertexAry[12] =
	{ glm::vec3(0.631f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[13] =
	{ glm::vec3(0.631f, 0.508f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[14] =
	{ glm::vec3(0.881f, 0.842f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[15] =
	{ glm::vec3(0.881f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 4
	cellVertexAry[16] =
	{ glm::vec3(-0.131f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[17] =
	{ glm::vec3(-0.131f, 0.175f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[18] =
	{ glm::vec3(0.119f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[19] =
	{ glm::vec3(0.119f, 0.175f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 5
	cellVertexAry[20] =
	{ glm::vec3(0.125f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[21] =
	{ glm::vec3(0.125f, 0.175f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[22] =
	{ glm::vec3(0.375f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[23] =
	{ glm::vec3(0.375f, 0.175f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 6
	cellVertexAry[24] =
	{ glm::vec3(0.378f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[25] =
	{ glm::vec3(0.378f, 0.175f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[26] =
	{ glm::vec3(0.622f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[27] =
	{ glm::vec3(0.622f, 0.175f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 7
	cellVertexAry[28] =
	{ glm::vec3(0.631f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[29] =
	{ glm::vec3(0.631f, 0.175f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[30] =
	{ glm::vec3(0.881f, 0.508f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[31] =
	{ glm::vec3(0.881f, 0.175f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 8
	cellVertexAry[32] =
	{ glm::vec3(-0.131f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[33] =
	{ glm::vec3(-0.131f, -0.167f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[34] =
	{ glm::vec3(0.119f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[35] =
	{ glm::vec3(0.119f, -0.167f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 9
	cellVertexAry[36] =
	{ glm::vec3(0.125f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[37] =
	{ glm::vec3(0.125f, -0.167f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[38] =
	{ glm::vec3(0.375f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[39] =
	{ glm::vec3(0.375f, -0.167f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 10
	cellVertexAry[40] =
	{ glm::vec3(0.378f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[41] =
	{ glm::vec3(0.378f, -0.167f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[42] =
	{ glm::vec3(0.622f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[43] =
	{ glm::vec3(0.622f, -0.167f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 11
	cellVertexAry[44] =
	{ glm::vec3(0.631f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[45] =
	{ glm::vec3(0.631f, -0.167f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[46] =
	{ glm::vec3(0.881f, 0.167f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[47] =
	{ glm::vec3(0.881f, -0.167f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 12
	cellVertexAry[48] =
	{ glm::vec3(-0.131f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[49] =
	{ glm::vec3(-0.131f, -0.5f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[50] =
	{ glm::vec3(0.119f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[51] =
	{ glm::vec3(0.119f, -0.5f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 13
	cellVertexAry[52] =
	{ glm::vec3(0.125f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[53] =
	{ glm::vec3(0.125f, -0.5f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[54] =
	{ glm::vec3(0.375f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[55] =
	{ glm::vec3(0.375f, -0.5f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 14
	cellVertexAry[56] =
	{ glm::vec3(0.378f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[57] =
	{ glm::vec3(0.378f, -0.508f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[58] =
	{ glm::vec3(0.622f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[59] =
	{ glm::vec3(0.622f, -0.508f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 15
	cellVertexAry[60] =
	{ glm::vec3(0.631f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[61] =
	{ glm::vec3(0.631f, -0.5f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[62] =
	{ glm::vec3(0.881f, -0.175f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[63] =
	{ glm::vec3(0.881f, -0.5f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 16
	cellVertexAry[64] =
	{ glm::vec3(-0.131f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[65] =
	{ glm::vec3(-0.131f, -0.838f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[66] =
	{ glm::vec3(0.119f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[67] =
	{ glm::vec3(0.119f, -0.838f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 17
	cellVertexAry[68] =
	{ glm::vec3(0.125f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[69] =
	{ glm::vec3(0.125f, -0.838f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[70] =
	{ glm::vec3(0.375f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[71] =
	{ glm::vec3(0.375f, -0.838f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 18
	cellVertexAry[72] =
	{ glm::vec3(0.378f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[73] =
	{ glm::vec3(0.378f, -0.838f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[74] =
	{ glm::vec3(0.622f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[75] =
	{ glm::vec3(0.622f, -0.838f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };
	// cell 19
	cellVertexAry[76] =
	{ glm::vec3(0.631f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 0.0),
	  glm::vec2(0.0f, 1.0f), };
	cellVertexAry[77] =
	{ glm::vec3(0.631f, -0.838f, 0.0f),
	  glm::vec3(0.0f, 1.0f, 0.0f),
	  glm::vec2(0.0f, 0.0f), };
	cellVertexAry[78] =
	{ glm::vec3(0.881f, -0.513f, 0.0f),
	  glm::vec3(1.0f, 0.0f, 1.0f),
	  glm::vec2(1.0f, 1.0f), };
	cellVertexAry[79] =
	{ glm::vec3(0.881f, -0.838f, 0.0f),
	  glm::vec3(1.0f, 1.0f, 0.0f),
	  glm::vec2(1.0f, 0.0f), };


}

void initIndices(GLuint indices[])
{
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 3; j++) {
			indices[i * 6 + j] = i * 4 + j;
			indices[i * 6 + j + 3] = indices[i * 6 + j] + 1;
		}

	/*
		// obj 0
		0, 1, 2,
		1, 2, 3,

		// obj 1
		4, 5, 6,
		5, 6, 7,

		// obj 2
		8, 9, 10,
		9, 10, 11,

		// obj 3
		12, 13, 14,
		13, 14, 15,

		// obj 4
		16, 17, 18,
		17, 18, 19,

		// obj 5
		20, 21, 22,
		21, 22, 23,

		// obj 6
		24, 25, 26,
		25, 26, 27,

		// obj 7
		28, 29, 30,
		29, 30, 31,

		// obj 8
		32, 33, 34,
		33, 34, 35,

		// obj 9
		36, 37, 38,
		37, 38, 39,

		// obj 10
		40, 41, 42,
		41, 42, 43,

		// obj 11
		44, 45, 46,
		45, 46, 47,

		// obj 12
		48, 49, 50,
		49, 50, 51,

		// obj 13
		52, 53, 54,
		53, 54, 55,

		// obj 14
		56, 57, 58,
		57, 58, 59,

		// obj 15
		60, 61, 62,
		61, 62, 63,

		// obj 16
		64, 65, 66,
		65, 66, 67,

		// obj 17
		68, 69, 70,
		69, 70, 71,

		// obj 18
		72, 73, 74,
		73, 74, 75,

		// obj 19
		76, 77, 78,
		77, 78, 79,

		// obj 20
		80, 81, 82,
		81, 82, 83
	*/
}

void updateVertexAray(Vertex myVertexAry[], 
	Vertex cellVertexAry[], int posMatrix[]) {
	int topLeftObjCell;

	// update obj 0 position
	for (int i = 0; i < 20; i++) {
		if (*(posMatrix + i) == 0) {
			topLeftObjCell = i;
			i = 20;
		}
	}
	//update 2 top corners
	myVertexAry[0] = cellVertexAry[topLeftObjCell * 4];
	myVertexAry[2] = cellVertexAry[topLeftObjCell * 4 + 2];

	//update 2 bottom corners
	myVertexAry[1] = cellVertexAry[(topLeftObjCell + 4) * 4 + 1];
	myVertexAry[3] = cellVertexAry[(topLeftObjCell + 4) * 4 + 3];	

	// update obj 2 position
	for (int i = 0; i < 20; i++) {
		if (*(posMatrix + i) == 2) {
			topLeftObjCell = i;
			i = 20;
		}
	}
	//update 2 top corners
	myVertexAry[2 * 4] = cellVertexAry[topLeftObjCell * 4];
	myVertexAry[2 * 4 + 2] = cellVertexAry[topLeftObjCell * 4 + 2];

	//update 2 bottom corners
	myVertexAry[2 * 4 + 1] = 
		cellVertexAry[(topLeftObjCell + 4) * 4 + 1];
	myVertexAry[2 * 4 + 3] = 
		cellVertexAry[(topLeftObjCell + 4) * 4 + 3];

	// update obj 3 position
	for (int i = 0; i < 20; i++) {
		if (*(posMatrix + i) == 3) {
			topLeftObjCell = i;
			i = 20;
		}
	}
	//update 2 top corners
	myVertexAry[3 * 4] = cellVertexAry[topLeftObjCell * 4];
	myVertexAry[3 * 4 + 2] = cellVertexAry[topLeftObjCell * 4 + 2];

	//update 2 bottom corners
	myVertexAry[3 * 4 + 1] = 
		cellVertexAry[(topLeftObjCell + 4) * 4 + 1];
	myVertexAry[3 * 4 + 3] = 
		cellVertexAry[(topLeftObjCell + 4) * 4 + 3];	

	// update obj 5 position
	for (int i = 0; i < 20; i++) {
		if (*(posMatrix + i) == 5) {
			topLeftObjCell = i;
			i = 20;
		}
	}
	//update 2 top corners
	myVertexAry[5 * 4] = cellVertexAry[topLeftObjCell * 4];
	myVertexAry[5 * 4 + 2] = cellVertexAry[topLeftObjCell * 4 + 2];

	//update 2 bottom corners
	myVertexAry[5 * 4 + 1] = 
		cellVertexAry[(topLeftObjCell + 4) * 4 + 1];
	myVertexAry[5 * 4 + 3] = 
		cellVertexAry[(topLeftObjCell + 4) * 4 + 3];

	// update obj 4 position
	for (int i = 0; i < 20; i++) {
		if (*(posMatrix + i) == 4) {
			topLeftObjCell = i;
			i = 20;
		}
	}
	//update 2 top corners
	myVertexAry[4 * 4] = cellVertexAry[topLeftObjCell * 4];
	myVertexAry[4 * 4 + 2] = 
		cellVertexAry[(topLeftObjCell + 1) * 4 + 2];

	//update 2 bottom corners
	myVertexAry[4 * 4 + 1] = 
		cellVertexAry[(topLeftObjCell) * 4 + 1];
	myVertexAry[4 * 4 + 3] = 
		cellVertexAry[(topLeftObjCell + 1) * 4 + 3];

	// update obj 1 position
	for (int i = 0; i < 20; i++) {
		if (*(posMatrix + i) == 1) {
			topLeftObjCell = i;
			i = 20;
		}
	}
	//update 2 top corners
	myVertexAry[4] = cellVertexAry[topLeftObjCell * 4];
	myVertexAry[6] = cellVertexAry[(topLeftObjCell + 1) * 4 + 2];

	//update 2 bottom corners
	myVertexAry[5] = cellVertexAry[(topLeftObjCell + 4) * 4 + 1];
	myVertexAry[7] = cellVertexAry[(topLeftObjCell + 5) * 4 + 3];

	// update obj 6 position
	for (int i = 0; i < 20; i++) {
		if (*(posMatrix + i) == 6) {
			topLeftObjCell = i;
			i = 20;
		}
	}
	//update 2 top corners
	myVertexAry[6 * 4] = cellVertexAry[topLeftObjCell * 4];
	myVertexAry[6 * 4 + 2] = cellVertexAry[topLeftObjCell * 4 + 2];

	//update 2 bottom corners
	myVertexAry[6 * 4 + 1] = cellVertexAry[topLeftObjCell * 4 + 1];
	myVertexAry[6 * 4 + 3] = cellVertexAry[topLeftObjCell * 4 + 3];

	// update obj 7 position
	for (int i = 0; i < 20; i++) {
		if (*(posMatrix + i) == 7) {
			topLeftObjCell = i;
			i = 20;
		}
	}
	//update 2 top corners
	myVertexAry[7 * 4] = cellVertexAry[topLeftObjCell * 4];
	myVertexAry[7 * 4 + 2] = cellVertexAry[topLeftObjCell * 4 + 2];

	//update 2 bottom corners
	myVertexAry[7 * 4 + 1] = cellVertexAry[topLeftObjCell * 4 + 1];
	myVertexAry[7 * 4 + 3] = cellVertexAry[topLeftObjCell * 4 + 3];

	// update obj 8 position
	for (int i = 0; i < 20; i++) {
		if (*(posMatrix + i) == 8) {
			topLeftObjCell = i;
			i = 20;
		}
	}
	//update 2 top corners
	myVertexAry[8 * 4] = cellVertexAry[topLeftObjCell * 4];
	myVertexAry[8 * 4 + 2] = cellVertexAry[topLeftObjCell * 4 + 2];

	//update 2 bottom corners
	myVertexAry[8 * 4 + 1] = cellVertexAry[topLeftObjCell * 4 + 1];
	myVertexAry[8 * 4 + 3] = cellVertexAry[topLeftObjCell * 4 + 3];

	// update obj 9 position
	for (int i = 0; i < 20; i++) {
		if (*(posMatrix + i) == 9) {
			topLeftObjCell = i;
			i = 20;
		}
	}
	//update 2 top corners
	myVertexAry[9 * 4] = cellVertexAry[topLeftObjCell * 4];
	myVertexAry[9 * 4 + 2] = cellVertexAry[topLeftObjCell * 4 + 2];

	//update 2 bottom corners
	myVertexAry[9 * 4 + 1] = cellVertexAry[topLeftObjCell * 4 + 1];
	myVertexAry[9 * 4 + 3] = cellVertexAry[topLeftObjCell * 4 + 3];
}

void printVertexAry(Vertex myVertexAry[]) {
	for (int i = 0; i < 19; i++) 
		for (int j = 0; j < 4; j++) {
			cout << "\nVertex " << i * 4 + j << " = " 
				<< myVertexAry[i * 4 + j].position.s;
		}		
}
