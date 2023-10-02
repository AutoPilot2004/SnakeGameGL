#include "Fruit.h"
#include "GameSettings.h"
#include "BodyPart.h"

#include <engine/ResourceManager.h>

Fruit::Fruit()
{
	//m_texture = engine::ResourceManager::getTexture("textures/fruit/fruit.png");
}

Fruit::~Fruit()
{

}

void Fruit::init(const std::vector<BodyPart*>& player)
{
	updatePosition(player);
}


void Fruit::updatePosition(const std::vector<BodyPart*>& player)
{
	m_position = { ((rand() % (BOARD_WIDTH - 2)) + 1) * TILE_SIZE, ((rand() % (BOARD_HEIGHT - 2)) + 1) * TILE_SIZE };

	for (int i = 0; i < player.size(); i++) {
		if (m_position == player[i]->getPosition()) {
			m_position = { ((rand() % BOARD_WIDTH - 2) + 2) * TILE_SIZE, ((rand() % BOARD_HEIGHT - 2) + 2) * TILE_SIZE };
			i = -1;
		}
	}
}

void Fruit::draw(engine::SpriteBatch& renderBatch)
{
	renderBatch.draw({ m_position, TILE_SIZE, TILE_SIZE }, { 0.0f, 0.0f, 1.0f, 1.0f }, engine::ResourceManager::getTexture("assets/textures/fruit/fruit.png").id, 1.0f, { 255, 255, 255, 255 });
}