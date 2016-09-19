#pragma once
#include <string>
#include <GL/glew.h>
#include "GLTexture.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "EngineError.h"

class ImageLoader {
public:
	static GLTexture LoadPNG(std::string a_filePath);
};