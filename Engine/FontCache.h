#pragma once
#include "Font.h"
#include <map>

namespace Engine {

	class FontCache
	{
	public:
		FontCache();
		~FontCache();
		Font getFont(std::string a_filePath);
	private:
		std::map<std::string, Font> _fontMap;
	};

}