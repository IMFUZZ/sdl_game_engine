#pragma once
#include <string>
#include <GL/glew.h>
#include "GLTexture.h"
#include "PicoPNG.h"
#include "IOManager.h"
#include "EngineError.h"

namespace Engine {

	class ImageLoader {
	public:
		static GLTexture loadPNG(std::string a_filePath);
	};

}