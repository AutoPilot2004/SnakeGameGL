#pragma once
#include <engine/SpriteBatch.h>

class Board
{
public:
	Board();
	~Board();

	void init();

	void render();

private:
	engine::SpriteBatch m_boardBatch;
};