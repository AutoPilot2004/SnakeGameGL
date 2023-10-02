#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

namespace engine
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		//Setters
		static void setMouseCoords(double x, double y) { m_mouseCoords.x = x; m_mouseCoords.y = y; }

		//Getters
		static inline glm::dvec2 getMouseCoords() { return m_mouseCoords; }

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		bool isKeyPressed(unsigned int keyID);

	private:
		std::unordered_map<unsigned int, bool> m_keyMap;

		static glm::dvec2 m_mouseCoords;
	};
}