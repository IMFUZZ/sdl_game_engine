#pragma once
#include <GL/glew.h>
#include <string>
#include <cstddef>
#include "vertex.h"
#include "GLTexture.h"

class Sprite {
public:
	Sprite();
	Sprite(float a_x, float a_y, float a_width, float a_height, std::string a_texturePath, float a_depth, Color a_color);
	~Sprite();
	void init(float a_x, float a_y, float a_width, float a_height, std::string a_texturePath, float a_depth, Color a_color);
	void init(float a_x, float a_y, float a_width, float a_height, GLTexture a_texture, float a_depth, Color a_color);
	void setPosition(float a_x, float a_y);
	void setDimensions(float a_width, float a_height);
	void setTexture(std::string a_texturePath);
	void setTexture(GLTexture a_texture);
	void setColor(Color a_color);
	GLTexture getTexture() const;
	void draw();
	float x;
	float y;
	float width;
	float height;
	float depth;
	Color color;
protected:
	GLTexture _texture;
	GLuint _vboID;
};