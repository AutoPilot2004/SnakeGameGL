#include "GLSLProgram.h"
#include <iostream>
#include <fstream>

namespace engine
{
	GLSLProgram::GLSLProgram()
		: m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
	{

	}

	GLSLProgram::~GLSLProgram()
	{

	}

	void GLSLProgram::compileShaders(const std::string& vertFilePath, const std::string& fragFilePath)
	{
		compileShader(vertFilePath, m_vertexShaderID, GL_VERTEX_SHADER);
		compileShader(fragFilePath, m_fragmentShaderID, GL_FRAGMENT_SHADER);
	}

	void GLSLProgram::linkShaders()
	{
		m_programID = glCreateProgram();

		glAttachShader(m_programID, m_vertexShaderID);
		glAttachShader(m_programID, m_fragmentShaderID);

		glLinkProgram(m_programID);

		glDetachShader(m_programID, m_vertexShaderID);
		glDetachShader(m_programID, m_fragmentShaderID);

		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);
	}

	void GLSLProgram::compileShader(const std::string& filePath, GLuint& id, GLenum type)
	{
		id = glCreateShader(type);

		if (id == 0) {
			glfwTerminate();
			printf("Couldn't create shader!\n");
			std::cin.get();
			std::exit(1);
		}

		std::ifstream file(filePath);

		if (file.fail()) {
			glfwTerminate();
			perror(filePath.c_str());
			std::cin.get();
			std::exit(1);
		}

		std::string fileContents;
		std::string line;

		while (std::getline(file, line)) {
			fileContents += line + "\n";
		}

		file.close();

		const char* fileContPointer = fileContents.c_str();
		glShaderSource(id, 1, &fileContPointer, nullptr);

		glCompileShader(id);
	}

	void GLSLProgram::bind()
	{
		glUseProgram(m_programID);
	}

	void GLSLProgram::unbind()
	{
		glUseProgram(0);
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(m_programID, uniformName.c_str());

		if (location == GL_INVALID_INDEX) {
			glfwTerminate();
			std::cout << "Uniform '" << uniformName << "' not found in shader!\n";
			std::cin.get();
			std::exit(1);
		}

		return location;
	}
}