#pragma once
#include <glm/glm.hpp>
#include <engine/SpriteBatch.h>
#include <engine/GLTexture.h>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class BodyPart
{
public:
	BodyPart();
	virtual ~BodyPart();

	void update(Direction dirOfInFront, Direction prevDirOfInFront);

	void draw(engine::SpriteBatch& renderBatch);

	void updateTexture(engine::GLTexture newTexture) { if (m_texture == m_originalTexture) { m_originalTexture = newTexture; m_texture = m_originalTexture; } else m_originalTexture = newTexture; }

	//Getters
	inline const glm::vec2& getPosition() const { return m_position; }

	inline Direction getPrevDir() const { return m_prevDir; }
	inline Direction getCurrentDir() const { return m_currentDir; }

protected:
	void checkIfOutOfBoard();

protected:
	glm::vec2 m_position;
	float m_rotation;

	Direction m_currentDir;
	Direction m_prevDir;

	engine::GLTexture m_texture;
	engine::GLTexture m_originalTexture;

private:

};

