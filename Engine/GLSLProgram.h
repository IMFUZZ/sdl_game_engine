
#define GLEW_STATIC

#include <string>
#include <fstream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>

#include "EngineError.h"

using namespace std;

class GLSLProgram {
	
	public:
		GLSLProgram();
		~GLSLProgram();
		void compileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath);
		void linkShaders();
		void addAttribute(const std::string& a_attributeName);
		GLint getUniformLocation(const std::string& a_uniformName);
		void use();
		void unuse();

	private:
		int _numAttributes;
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		void compileShader(const std::string a_shaderFilePath, GLuint id);
};