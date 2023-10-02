#include "Window.h"

#include <iostream>

namespace engine
{
	Window::Window()
		: m_window(nullptr), m_sWidth(0), m_sHeight(0)
	{

	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::create(const std::string& title, int screenWidth, int screenHeight, const glm::vec4& backgroundColor)
	{
		m_window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);

		m_sWidth = screenWidth;
		m_sHeight = screenHeight;

		if (!m_window) {
			glfwTerminate();
			std::cout << "Couldn't initialize GLFW Window!\n";
			std::cin.get();
			std::exit(1);
		}

		glfwMakeContextCurrent(m_window);

		if (glewInit() != GLEW_OK) {
			glfwTerminate();
			std::cout << "Couldn't initialize GLEW!\n";
			std::cin.get();
			std::exit(1);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glEnable(GL_DEPTH_TEST);

		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		glClearDepth(1.0f);
	}

	void Window::update()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void Window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	int Window::isClosed() const
	{
		int isClosed = glfwWindowShouldClose(m_window);

		if (isClosed)
			glfwTerminate();

		return isClosed;
	}
}