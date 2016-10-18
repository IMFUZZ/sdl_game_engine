#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
#include "Sprite.h"

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class Glyph {
public:
	Glyph() {};
	Glyph(const glm::vec4 & a_destRect, const glm::vec4 & a_uvRect, const GLuint a_texture, const float a_depth, const Color & a_color) :
		texture(a_texture), 
		depth(a_depth) 
	{
		topLeft.color = a_color;
		topLeft.setPosition(a_destRect.x, a_destRect.y + a_destRect.w);
		topLeft.setUV(a_uvRect.x, a_uvRect.y + a_uvRect.w);

		bottomLeft.color = a_color;
		bottomLeft.setPosition(a_destRect.x, a_destRect.y);
		bottomLeft.setUV(a_uvRect.x, a_uvRect.y);

		bottomRight.color = a_color;
		bottomRight.setPosition(a_destRect.x + a_destRect.z, a_destRect.y);
		bottomRight.setUV(a_uvRect.x + a_uvRect.z, a_uvRect.y);

		topRight.color = a_color;
		topRight.setPosition(a_destRect.x + a_destRect.z, a_destRect.y + a_destRect.w);
		topRight.setUV(a_uvRect.x + a_uvRect.z, a_uvRect.y + a_uvRect.w);
	};

	GLuint texture;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex bottomRight;
	Vertex topRight;
};

class RenderBatch {
public:
	RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {

	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();
	void init();
	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& a_destRect, const glm::vec4& a_uvRect, const GLuint a_texture, const float a_depth, const Color& a_color);
	void draw(const glm::vec4& a_destRect, const Sprite& a_sprite);
	void renderBatch();

private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

	std::vector<Glyph*> _glyphPointers; // This is for sorting
	std::vector<Glyph> _glyphs; // These are the actual glyphs
	std::vector<RenderBatch> _renderBatches;

	GlyphSortType _sortType;

	GLuint _vbo;
	GLuint _vao;
};

