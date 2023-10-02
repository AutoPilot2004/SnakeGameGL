#pragma once
#include "BodyPart.h"
#include <GLFW/glfw3.h>

class Head : public BodyPart
{
public:
	Head(GLFWwindow* window);
	~Head() override;

	void updateDir();
	void update();

private:
	GLFWwindow* m_window;

	bool hasUpdated;
};

