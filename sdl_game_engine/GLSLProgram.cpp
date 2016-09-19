
#include "GLSLProgram.h"

GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0) {

}

GLSLProgram::~GLSLProgram() {

}


void GLSLProgram::CompileShaders(const string& a_vertexShaderFilePath, const string& a_fragmentShaderFilePath) {
	_programID = glCreateProgram();
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("Vertex shader failed to be created");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		fatalError("Fragment shader failed to be created");
	}

	CompileShader(a_vertexShaderFilePath, _vertexShaderID);
	CompileShader(a_fragmentShaderFilePath, _fragmentShaderID);
}

void GLSLProgram::CompileShader(const std::string a_shaderFilePath, GLuint id) {
	std::ifstream shaderFile(a_shaderFilePath);
	if (shaderFile.fail()) {
		fatalError("Failed to open " + a_shaderFilePath);
	}
	std::string fileContents = "";
	std::string line = "";
	while (std::getline(shaderFile, line)) {
		fileContents += line + "\n";
	}
	shaderFile.close();
	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Could not compile shader : " + a_shaderFilePath);
	}
}

void GLSLProgram::LinkShaders() {
	//Attach our shaders to our _programID
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our _programID
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the _programID anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shaders failed to link!");
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::AddAttribute(const std::string& a_attributeName) {
	glBindAttribLocation(_programID, _numAttributes, a_attributeName.c_str());
	_numAttributes++;
}

void GLSLProgram::Use() {
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::Unuse() {
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

GLint GLSLProgram::GetUniformLocation(const std::string& a_uniformName) {
	GLint location = glGetUniformLocation(_programID, a_uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform " + a_uniformName + " not found in shader!");
	}
	return location;
}