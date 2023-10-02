#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace engine
{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertFilePath, const std::string& fragFilePath);

		void linkShaders();

		void bind();
		void unbind();

		GLint getUniformLocation(const std::string& uniformName);

	private:
		void compileShader(const std::string& filePath, GLuint& id, GLenum type);

		GLuint m_programID;

		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
	};
}