#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>

namespace engine
{
	class Window
	{
	public:
		Window();
		~Window();

		void create(const std::string& title, int screenWidth, int screenHeight, const glm::vec4& backgroundColor);

		void update();

		void clear();

		int isClosed() const;

		//Getters
		inline GLFWwindow* getWindow() const { return m_window; }

		inline int getScreenWidth() const { return m_sWidth; }
		inline int getScreenHeight() const { return m_sHeight; }

	private:
		GLFWwindow* m_window;

		int m_sWidth;
		int m_sHeight;
	};
}