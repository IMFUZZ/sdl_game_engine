#include "Sprite.h"
#include "ResourcesManager.h"

namespace Engine {

	Sprite::Sprite() : _vboID(0) {}

	Sprite::Sprite(float a_x, float a_y, float a_width, float a_height, float a_depth/* = 1.0f*/, Color a_color/* = { 255, 255, 255, 255 }*/)
		: _vboID(0), x(a_x), y(a_y), width(a_width), height(a_height), depth(a_depth), color(a_color) 
	{}

	Sprite::Sprite(float a_x, float a_y, float a_width, float a_height, std::string a_texturePath, float a_depth/* = 1.0f*/, Color a_color/* = { 255, 255, 255, 255 }*/)
		: _vboID(0), x(a_x), y(a_y), width(a_width), height(a_height), depth(a_depth), color(a_color) 
	{
		init(a_texturePath);
	}

	Sprite::~Sprite() {
		if (_vboID != 0) glDeleteBuffers(1, &_vboID);
	}

	void Sprite::init(std::string a_texturePath) {
		setTexture(a_texturePath);
		initVertexData();
	}

	void Sprite::initVertexData() {
		if (_vboID != 0) return;
		glGenBuffers(1, &_vboID);
		Vertex vertexData[6];
		for (int i = 0; i < 6; i++) {
			switch (i) {
				case 0:
					vertexData[i].setPosition(x + width, y + height);
					vertexData[i].setUV(1.0f, 1.0f);
					break;
				case 1:
					vertexData[i].setPosition(x, y + height);
					vertexData[i].setUV(0.0f, 1.0f);
					break;
				case 2:
					vertexData[i].setPosition(x, y);
					vertexData[i].setUV(0.0f, 0.0f);
					break;
				case 3:
					vertexData[i].setPosition(x, y);
					vertexData[i].setUV(0.0f, 0.0f);
					break;
				case 4:
					vertexData[i].setPosition(x + width, y);
					vertexData[i].setUV(1.0f, 0.0f);
					break;
				case 5:
					vertexData[i].setPosition(x + width, y + height);
					vertexData[i].setUV(1.0f, 1.0f);
					break;
			}
			vertexData[i].setColor(color);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
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

	void Sprite::setTexture(std::string a_texturePath) {
		_texture = ResourcesManager::getTexture(a_texturePath);
	}

	void Sprite::setTexture(GLTexture a_texture) {
		_texture = a_texture;
	}

	void Sprite::draw() {
		if (_vboID == 0) {
			std::cout << "_vboID == 0!" << std::endl;
			return;
		}
		// THIS DOESN'T WORK - DJDUBE
		glBindTexture(GL_TEXTURE_2D, _texture.id);
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		
		glDrawArrays(GL_TRIANGLES, 0, 6); // Draw the 6 vertices on the screen : shape, first elem, number of elem (vertex)
		glDisableVertexAttribArray(0); // 0 is 0th index
		glDisableVertexAttribArray(1); // 1 is 1th index
		glDisableVertexAttribArray(2); // 2 is 2th index

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::move(float a_x, float a_y) {
		x += a_x;
		y += a_y;
	}

}