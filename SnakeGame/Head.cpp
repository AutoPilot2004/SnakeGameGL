#include "Head.h"
#include "GameSettings.h"

#include <engine/ResourceManager.h>

Head::Head(GLFWwindow* window)
{
	m_window = window;

	m_position = { ((rand() % (BOARD_WIDTH - 2)) + 1) * TILE_SIZE, ((rand() % (BOARD_HEIGHT - 2)) + 1) * TILE_SIZE };
	m_rotation = 90.0f;

	m_texture = engine::ResourceManager::getTexture("assets/textures/player/playerHead.png");

	m_currentDir = Direction::UP;
	m_prevDir = m_currentDir;

	hasUpdated = true;
}

Head::~Head()
{

}
//Delete hasUpdated check and put the updateDir inside the frameCount in GameSystem
void Head::updateDir()
{
	if (hasUpdated) {
		m_prevDir = m_currentDir;

		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS && m_currentDir != Direction::DOWN) {
			m_currentDir = Direction::UP;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS && m_currentDir != Direction::UP) {
			m_currentDir = Direction::DOWN;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS && m_currentDir != Direction::RIGHT) {
			m_currentDir = Direction::LEFT;
		}
		else if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS && m_currentDir != Direction::LEFT) {
			m_currentDir = Direction::RIGHT;
		}

		hasUpdated = false;
	}
}

void Head::update()
{
	switch (m_currentDir) {
	case Direction::UP:
		m_rotation = 90.0f;
		m_position += glm::vec2(0.0f, TILE_SIZE);
		break;
	case Direction::DOWN:
		m_rotation = -90.0f;
		m_position -= glm::vec2(0.0f, TILE_SIZE);
		break;
	case Direction::LEFT:
		m_rotation = 180.0f;
		m_position -= glm::vec2(TILE_SIZE, 0.0f);
		break;
	case Direction::RIGHT:
		m_rotation = 0.0f;
		m_position += glm::vec2(TILE_SIZE, 0.0f);
		break;
	}

	checkIfOutOfBoard();

	hasUpdated = true;
}