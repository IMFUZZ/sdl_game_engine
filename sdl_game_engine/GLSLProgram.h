
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
		void CompileShaders(const string& vertexShaderFilePath, const string& fragmentShaderFilePath);
		void LinkShaders();
		void AddAttribute(const std::string& a_attributeName);
		GLint GetUniformLocation(const std::string& a_uniformName);
		void Use();
		void Unuse();

	private:
		int _numAttributes;
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		void CompileShader(const std::string a_shaderFilePath, GLuint id);
};