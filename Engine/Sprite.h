#pragma once
#include <iostream>
#include <GL/glew.h>
#include <string>
#include <cstddef>
#include "Vertex.h"
#include "GLTexture.h"

namespace Engine {

	class Sprite {
	public:

		Sprite();
		Sprite(float a_x, float a_y, float a_width, float a_height, float a_depth = 1.0f, Color a_color = { 255, 255, 255, 255 });
		Sprite(float a_x, float a_y, float a_width, float a_height, std::string a_texturePath, float a_depth = 1.0f, Color a_color = { 255, 255, 255, 255 });
		~Sprite();
		
		float x;
		float y;
		float width;
		float height;
		float depth;
		Color color;

		void init(std::string a_texturePath);
		void initVertexData();

		void drawRect(float a_x, float a_y, float a_width, float a_height);
		void drawCircle(float a_x, float a_y, float a_radius);

		void move(float a_x, float a_y);
		void setPosition(float a_x, float a_y);
		void setDimensions(float a_width, float a_height);
		void setTexture(std::string a_texturePath);
		void setTexture(GLTexture a_texture);
		void setColor(Color a_color);
		void draw();

		// Getters
		GLTexture getTexture() const { return _texture; }
	protected:
		GLTexture _texture;
		GLuint _vboID;
	};

}