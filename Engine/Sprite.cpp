
#include "Sprite.h"
#include "ResourcesManager.h"

Sprite::Sprite() {
	_vboID = 0;
}

Sprite::Sprite(float a_x, float a_y, float a_width, float a_height, std::string a_texturePath, float a_depth, Color a_color) {
	setTexture(a_texturePath);
	init(a_x, a_y, a_width, a_height, _texture, a_depth, a_color);
}

Sprite::~Sprite() {
	if (_vboID != 0)
		glDeleteBuffers(1, &_vboID);
}

void Sprite::init(float a_x, float a_y, float a_width, float a_height, std::string a_texturePath, float a_depth, Color a_color) {
	setTexture(a_texturePath);
	init(a_x, a_y, a_width, a_height, _texture, a_depth, a_color);
}

void Sprite::init(float a_x, float a_y, float a_width, float a_height, GLTexture a_texture, float a_depth, Color a_color) {
	setPosition(a_x, a_y);
	setDimensions(a_width, a_height);
	setTexture(a_texture);
	setColor(a_color);
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
		Vertex vertexData[6];
		for (int i = 0; i < 6; i++) {
			switch (i) {
			case 0:
				vertexData[i].setPosition(a_x + a_width, a_y + a_height);
				vertexData[i].setUV(1.0f, 1.0f);
				break;
			case 1:
				vertexData[i].setPosition(a_x, a_y + a_height);
				vertexData[i].setUV(0.0f, 1.0f);
				break;
			case 2:
				vertexData[i].setPosition(a_x, a_y);
				vertexData[i].setUV(0.0f, 0.0f);
				break;
			case 3:
				vertexData[i].setPosition(a_x, a_y);
				vertexData[i].setUV(0.0f, 0.0f);
				break;
			case 4:
				vertexData[i].setPosition(a_x + a_width, a_y);
				vertexData[i].setUV(1.0f, 0.0f);
				break;
			case 5:
				vertexData[i].setPosition(a_x + a_width, a_y + a_height);
				vertexData[i].setUV(1.0f, 1.0f);
				break;
			}
			vertexData[i].setColor(color);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Sprite::setPosition(float a_x, float a_y) {
	x = a_x;
	y = a_y;
}

void Sprite::setDimensions(float a_width, float a_height) {
	width = a_width;
	height = a_height;
}
void Sprite::setColor(Color a_color) {
	color = a_color;
}

GLTexture Sprite::getTexture() const {
	return _texture;
}

void Sprite::setTexture(std::string a_texturePath) {
	_texture = ResourcesManager::getTexture(a_texturePath);
}

void Sprite::setTexture(GLTexture a_texture) {
	_texture = a_texture;
}

void Sprite::draw() {
	// THIS DOESN'T WORK - DJDUBE
	glBindTexture(GL_TEXTURE_2D, _texture.id);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	
	glDrawArrays(GL_TRIANGLES, 0, 6); // Draw the 6 vertices on the screen : shape, first elem, number of elem (vertex)
	glDisableVertexAttribArray(0); // 0 is 0th index
	glDisableVertexAttribArray(1); // 1 is 1th index
	glDisableVertexAttribArray(2); // 2 is 2th index

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}