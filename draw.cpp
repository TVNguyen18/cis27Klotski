/**
* Program Name: KlotSki Game
* Discussion  : draw.cpp
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#include "draw.h"

void loadTexture(GLuint texture[], unsigned char* image, 
	int i, int w, int h) {
	glBindTexture(GL_TEXTURE_2D, texture[i]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, 
			GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		cout << "ERROR::TEXTURE_LOADING_FAIL!" << endl;
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	SOIL_free_image_data(image);
}

void bindAndDrawTexture(GLuint textureIDAry[], 
	GLuint shaderProgramID) {
	// draw	obj 0	

	// activate texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[0]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//draw obj 1
	glActiveTexture(1);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[1]);

	glUniform1i(glGetUniformLocation(shaderProgramID, 
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(6 * sizeof(int)));

	//draw obj 2
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[0]);

	glUniform1i(glGetUniformLocation(shaderProgramID,
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(12 * sizeof(int)));


	//draw obj 3
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[0]);

	glUniform1i(glGetUniformLocation(shaderProgramID, 
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(18 * sizeof(int)));

	//draw obj 4
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[2]);

	glUniform1i(glGetUniformLocation(shaderProgramID,
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(24 * sizeof(int)));

	//draw obj 5
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[0]);

	glUniform1i(glGetUniformLocation(shaderProgramID, 
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(30 * sizeof(int)));

	//draw obj 6
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[3]);

	glUniform1i(glGetUniformLocation(shaderProgramID, 
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(36 * sizeof(int)));

	//draw obj 7
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[3]);

	glUniform1i(glGetUniformLocation(shaderProgramID, 
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(42 * sizeof(int)));

	//draw obj 8
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[3]);

	glUniform1i(glGetUniformLocation(shaderProgramID, 
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
		(const void*)(48 * sizeof(int)));

	//draw obj 9
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[3]);

	glUniform1i(glGetUniformLocation(shaderProgramID, 
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
		(const void*)(54 * sizeof(int)));

	//draw obj 10
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[4]);

	glUniform1i(glGetUniformLocation(shaderProgramID, 
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(60 * sizeof(int)));

	//draw obj 11
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[4]);

	glUniform1i(glGetUniformLocation(shaderProgramID,
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(66 * sizeof(int)));

	//draw obj 12
	glActiveTexture(4);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[4]);

	glUniform1i(glGetUniformLocation(shaderProgramID,
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
		(const void*)(72 * sizeof(int)));

	//draw obj 13
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[4]);

	glUniform1i(glGetUniformLocation(shaderProgramID,
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
		(const void*)(78 * sizeof(int)));

	//draw obj 14
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[4]);

	glUniform1i(glGetUniformLocation(shaderProgramID,
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
		(const void*)(84 * sizeof(int)));

	//draw obj 15 - logo
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[5]);

	glUniform1i(glGetUniformLocation(shaderProgramID,
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
		(const void*)(90 * sizeof(int)));

	//draw obj 16 - undo_button
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[6]);

	glUniform1i(glGetUniformLocation(shaderProgramID, 
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(96 * sizeof(int)));

	//drawobj 17 - reset_button
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[7]);

	glUniform1i(glGetUniformLocation(shaderProgramID,
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
		(const void*)(102 * sizeof(int)));

	//draw exit_button
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[8]);

	glUniform1i(glGetUniformLocation(shaderProgramID,
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
		(const void*)(108 * sizeof(int)));

	
	//draw sol_button
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIDAry[9]);

	glUniform1i(glGetUniformLocation(shaderProgramID,
		"my_Texture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 
		(const void*)(114 * sizeof(int)));
}