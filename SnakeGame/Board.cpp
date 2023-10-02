#include "Board.h"

#include <engine/ResourceManager.h>
#include "GameSettings.h"

Board::Board()
{

}

Board::~Board()
{

}

void Board::init()
{
	m_boardBatch.init();

	m_boardBatch.begin();

	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (i == 0 || i == BOARD_HEIGHT - 1 || j == 0 || j == BOARD_WIDTH - 1) m_boardBatch.draw({ j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE }, { 0.0f, 0.0f, 1.0f, 1.0f }, engine::ResourceManager::getTexture("assets/textures/board/grass.png").id, 1.0f, { 200, 200, 200, 255 });
			else if ((j + i) % 2 == 0) m_boardBatch.draw({ j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE }, { 0.0f, 0.0f, 1.0f, 1.0f }, engine::ResourceManager::getTexture("assets/textures/board/grass.png").id, 1.0f, { 255, 255, 255, 255 });
			else m_boardBatch.draw({ j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE }, { 0.0f, 0.0f, 1.0f, 1.0f }, engine::ResourceManager::getTexture("assets/textures/board/grass2.png").id, 1.0f, { 255, 255, 255, 255 });
		}
	}

	m_boardBatch.end();
}

void Board::render()
{
	m_boardBatch.renderBatch();
}