#pragma once

#include <GL/glew.h>

struct Position { // type "Position"
	float x;
	float y;
}; // attribute "position"
struct Color { // type "Color"
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
}; // attribute "color"

struct Vertex {
	Position position;
	Color color;
};