#pragma once
#include <engine/Window.h>
#include <engine/GLSLProgram.h>
#include <engine/Camera2D.h>
#include <engine/SpriteBatch.h>

#include "Board.h"
#include "Fruit.h"

class Head;
class BodyPart;

class GameSystem
{
public:
	GameSystem();
	~GameSystem();

	void run();

private:
	void init();
	void initShaders();

	void gameLoop();

	void updatePlayerAndFruit();

	void render();

private:
	engine::Window m_window;
	int m_sWidth, m_sHeight;

	engine::GLSLProgram m_shaderProgram;

	engine::Camera2D m_camera;

	engine::SpriteBatch m_renderBatch;

	Board m_board;

	Head* m_playerHead;
	std::vector<BodyPart*> m_player;

	Fruit m_fruit;

	int m_frameCount;

	int m_score;
};

