#include "InputManager.h"

namespace engine
{
	glm::dvec2 InputManager::m_mouseCoords;

	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::pressKey(unsigned int keyID)
	{
		m_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID)
	{
		m_keyMap[keyID] = false;
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		if (m_keyMap.find(keyID) != m_keyMap.end())
			return m_keyMap[keyID];

		return false;
	}
}