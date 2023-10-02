#pragma once
#include <glm/glm.hpp>
#include <engine/GLTexture.h>
#include <engine/SpriteBatch.h>
#include <vector>

class BodyPart;

class Fruit
{
public:
	Fruit();
	~Fruit();

	void init(const std::vector<BodyPart*>& player);

	void updatePosition(const std::vector<BodyPart*>& player);

	void draw(engine::SpriteBatch& renderBatch);

	//Getters
	inline glm::vec2 getPosition() const { return m_position; }

private:
	glm::vec2 m_position;

	engine::GLTexture m_texture;
};

