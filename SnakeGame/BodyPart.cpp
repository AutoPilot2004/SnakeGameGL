#include "BodyPart.h"
#include <engine/ResourceManager.h>

#include "GameSettings.h"

BodyPart::BodyPart()
{

}

BodyPart::~BodyPart()
{

}

void BodyPart::update(Direction dirOfInFront, Direction prevDirOfInFront)
{
	m_prevDir = m_currentDir;
	m_currentDir = prevDirOfInFront;

	if ((m_currentDir == Direction::UP && dirOfInFront == Direction::LEFT) || (m_currentDir == Direction::RIGHT && dirOfInFront == Direction::DOWN))
		m_texture = engine::ResourceManager::getTexture("assets/textures/player/leftFromBottom.png");
	else if ((m_currentDir == Direction::UP && dirOfInFront == Direction::RIGHT) || (m_currentDir == Direction::LEFT && dirOfInFront == Direction::DOWN))
		m_texture = engine::ResourceManager::getTexture("assets/textures/player/rightFromBottom.png");
	else if ((m_currentDir == Direction::DOWN && dirOfInFront == Direction::RIGHT) || (m_currentDir == Direction::LEFT && dirOfInFront == Direction::UP))
		m_texture = engine::ResourceManager::getTexture("assets/textures/player/rightFromTop.png");
	else if ((m_currentDir == Direction::DOWN && dirOfInFront == Direction::LEFT) || (m_currentDir == Direction::RIGHT && dirOfInFront == Direction::UP))
		m_texture = engine::ResourceManager::getTexture("assets/textures/player/leftFromTop.png");
	else m_texture = m_originalTexture;

	m_rotation = 0.0f;

	switch (m_currentDir) {
	case Direction::UP:
		if (m_texture == m_originalTexture)
			m_rotation = 90.0f;
		m_position += glm::vec2(0.0f, TILE_SIZE);
		break;
	case Direction::DOWN:
		if (m_texture == m_originalTexture)
			m_rotation = -90.0f;
		m_position -= glm::vec2(0.0f, TILE_SIZE);
		break;
	case Direction::LEFT:
		if (m_texture == m_originalTexture)
			m_rotation = 180.0f;
		m_position -= glm::vec2(TILE_SIZE, 0.0f);
		break;
	case Direction::RIGHT:
		m_position += glm::vec2(TILE_SIZE, 0.0f);
		break;
	}

	checkIfOutOfBoard();
}

void BodyPart::draw(engine::SpriteBatch& renderBatch)
{
	renderBatch.draw({ m_position, TILE_SIZE, TILE_SIZE }, { 0.0f, 0.0f, 1.0f, 1.0f }, m_texture.id, 1.0f, { 255, 255, 255, 255 }, m_rotation);
}

void BodyPart::checkIfOutOfBoard()
{
	if (m_position.x < TILE_SIZE) m_position.x = (BOARD_WIDTH * TILE_SIZE) - (2 * TILE_SIZE);
	else if (m_position.x > (BOARD_WIDTH * TILE_SIZE) - (2 * TILE_SIZE)) m_position.x = TILE_SIZE;
	else if (m_position.y < TILE_SIZE) m_position.y = (BOARD_HEIGHT * TILE_SIZE) - (2 * TILE_SIZE);
	else if (m_position.y > (BOARD_HEIGHT * TILE_SIZE) - (2 * TILE_SIZE)) m_position.y = TILE_SIZE;
}