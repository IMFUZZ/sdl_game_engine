
#define GLEW_STATIC
#include <GL/glew.h>
#include <cstddef>
#include "vertex.h"

class Sprite {

public:
	Sprite();
	~Sprite();

	void Init(float a_x, float a_y, float a_width, float a_height);
	void Draw();
private:
	float _x;
	float _y;
	float _width;
	float _height;
	GLuint _vboID;
};