
#include "Sprite.h"

Sprite::Sprite() {
	_vboID = 0;
}

Sprite::~Sprite() {
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::Init(float a_x, float a_y, float a_width, float a_height) {
	_x = a_x;
	_y = a_y;
	_width = a_width;
	_height = a_height;

	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[12];

	// First triangle
	vertexData[0].position.x = a_x + a_width; // x 
	vertexData[0].position.y = a_y + a_height; // y

	vertexData[1].position.x = a_x;
	vertexData[1].position.y = a_y + a_height;

	vertexData[2].position.x = a_x;
	vertexData[2].position.y = a_y;

	// Second triangle
	vertexData[3].position.x = a_x;
	vertexData[3].position.y = a_y;

	vertexData[4].position.x = a_x + a_width;
	vertexData[4].position.y = a_y;

	vertexData[5].position.x = a_x + a_width;
	vertexData[5].position.y = a_y + a_height;

	for (int i = 0; i < 6; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 255;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0); // 0 is 0th index

								  // This is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // 0 is 0th index, 2 is for x and y, 
																										// This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); // 0 is 0th index, 2 is for x and y, 

																											// Draw the 6 vertices on the screen
	glDrawArrays(GL_TRIANGLES, 0, 6); // shape, first elem, number of elem (vertex)

	glDisableVertexAttribArray(0); // 0 is 0th index

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}