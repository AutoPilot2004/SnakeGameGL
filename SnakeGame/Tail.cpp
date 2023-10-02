#include "Tail.h"
#include "GameSettings.h"

Tail::Tail(engine::GLTexture texture, glm::vec2 posOfFront, Direction dirOfFront)
{
	if (dirOfFront == Direction::UP)
		m_position = { posOfFront.x, posOfFront.y - TILE_SIZE };
	else if (dirOfFront == Direction::DOWN)
		m_position = { posOfFront.x, posOfFront.y + TILE_SIZE };
	else if (dirOfFront == Direction::LEFT)
		m_position = { posOfFront.x + TILE_SIZE, posOfFront.y };
	else if (dirOfFront == Direction::RIGHT)
		m_position = { posOfFront.x - TILE_SIZE, posOfFront.y };

	switch (dirOfFront) {
	case Direction::UP:
		m_rotation = 90.0f;
		break;
	case Direction::DOWN:
		m_rotation = -90.0f;
		break;
	case Direction::LEFT:
		m_rotation = 180.0f;
		break;
	case Direction::RIGHT:
		m_rotation = 0.0f;
		break;
	}

	m_texture = texture;
	m_originalTexture = m_texture;

	m_currentDir = dirOfFront;
	m_prevDir = m_currentDir;
}

Tail::~Tail()
{

}