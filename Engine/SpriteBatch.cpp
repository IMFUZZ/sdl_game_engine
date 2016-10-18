#pragma once
#include "SpriteBatch.h"

#include <algorithm>

SpriteBatch::SpriteBatch() : 
	_vbo(0), _vao(0) 
{}


SpriteBatch::~SpriteBatch() {}

void SpriteBatch::init() {
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */) {
	_sortType = sortType;
	_renderBatches.clear();
	_glyphs.clear();
}

void SpriteBatch::end() {
	_glyphPointers.resize(_glyphs.size());
	for (int i = 0; i < _glyphs.size(); i++) { _glyphPointers[i] = &_glyphs[i]; }
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4 & a_destRect, const glm::vec4 & a_uvRect, const GLuint a_texture, const float a_depth, const Color & a_color) {
	_glyphs.emplace_back(a_destRect, a_uvRect, a_texture, a_depth, a_color);
}

void SpriteBatch::draw(const glm::vec4& a_destRect, const Sprite& a_sprite) {
	_glyphs.emplace_back(glm::vec4(0.0f, 0.0f, 32.0f, 32.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), a_sprite.getTexture().id, a_sprite.depth, a_sprite.color);
}

void SpriteBatch::renderBatch() {
	glBindVertexArray(_vao);
	for (size_t i = 0; i < _renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, _renderBatches.at(i).texture);
		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches() {
	std::vector<Vertex> vertices;
	vertices.resize(_glyphPointers.size() * 6);
	if (_glyphPointers.empty()) { return; }
	int 
		offset = 0, 
		cv = 0; // current vertex
	_renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
	vertices[cv++] = _glyphPointers[0]->topLeft;
	vertices[cv++] = _glyphPointers[0]->bottomLeft;
	vertices[cv++] = _glyphPointers[0]->bottomRight;
	vertices[cv++] = _glyphPointers[0]->bottomRight;
	vertices[cv++] = _glyphPointers[0]->topRight;
	vertices[cv++] = _glyphPointers[0]->topLeft;
	offset += 6;
	for (size_t cg = 1; cg < _glyphPointers.size(); cg++) {
		if (_glyphPointers[cg]->texture != _glyphPointers[cg - 1]->texture) {
			_renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
		} else {
			_renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = _glyphPointers[cg]->topLeft;
		vertices[cv++] = _glyphPointers[cg]->bottomLeft;
		vertices[cv++] = _glyphPointers[cg]->bottomRight;
		vertices[cv++] = _glyphPointers[cg]->bottomRight;
		vertices[cv++] = _glyphPointers[cg]->topRight;
		vertices[cv++] = _glyphPointers[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	// Orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray() {
	if (_vao == 0) { glGenVertexArrays(1, &_vao); }
	glBindVertexArray(_vao);
	if (_vbo == 0) { glGenBuffers(1, &_vbo); }
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glEnableVertexAttribArray(0); // 0 is 0th index
	glEnableVertexAttribArray(1); // 1 is 1th index
	glEnableVertexAttribArray(2); // 2 is 2th index
								  // This is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // 0 is 0th index, 2 is for x and y, 
																										// This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color)); // 0 is 0th index, 2 is for x and y, 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);

}

void SpriteBatch::sortGlyphs() {
	switch (_sortType) {
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
		break;
	}
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
	return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
	return (a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
	return (a->texture < b->texture);
}
