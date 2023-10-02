#include "engine.h"

#include <GLFW/glfw3.h>
#include <iostream>


namespace engine
{
	int init()
	{
		if (!glfwInit()) {
			std::cout << "Couldn't initialize GLFW!\n";
			std::cin.get();
			std::exit(1);
		}

		return 0;
	}
}