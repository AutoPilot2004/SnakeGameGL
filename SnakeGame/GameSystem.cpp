#include "GameSystem.h"
#include <engine/engine.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "Tail.h"
#include "BodyPart.h"
#include "Head.h"
#include "GameSettings.h"

#include <engine/ResourceManager.h>
#include <GL/glew.h>

GameSystem::GameSystem()
	: m_sWidth(1000), m_sHeight(1000), m_frameCount(0), m_score(0)
{
	srand(time(NULL));
}

GameSystem::~GameSystem()
{
	for (auto bodyPart : m_player)
		delete bodyPart;
}

void GameSystem::run()
{
	init();
	gameLoop();
}

void GameSystem::init()
{
	engine::init();

	m_window.create("SNAKE GAME", m_sWidth, m_sHeight, { 180/255.0f, 180/255.0f, 180/255.0f, 255/255.0f });

	initShaders();

	m_camera.init(m_sWidth, m_sHeight);
	m_camera.setPosition({ ((BOARD_WIDTH * TILE_SIZE) / 2.0f) - (TILE_SIZE / 2.0f), ((BOARD_HEIGHT * TILE_SIZE) / 2.0f) - (TILE_SIZE / 2.0f) });
	m_camera.setScale(0.7805f);
	m_camera.update();

	m_shaderProgram.bind();
	GLint textureLocation = m_shaderProgram.getUniformLocation("tex");
	glUniform1i(textureLocation, 0);

	GLint VPMatLocation = m_shaderProgram.getUniformLocation("VPMat");
	glUniformMatrix4fv(VPMatLocation, 1, GL_FALSE, &m_camera.getCameraMatrix()[0][0]);

	m_renderBatch.init();

	m_board.init();

	m_playerHead = new Head(m_window.getWindow());
	m_player.push_back(m_playerHead);

	m_fruit.init(m_player);
}

void GameSystem::initShaders()
{
	m_shaderProgram.compileShaders("assets/shaders/vert.vert.txt", "assets/shaders/frag.frag.txt");
	m_shaderProgram.linkShaders();
}

void GameSystem::gameLoop()
{
	using clock = std::chrono::high_resolution_clock;
	
	auto currentTime = clock::now();

	float updateRate = SPEED * (1/SPEED_FACTOR);
	float updateTimeCounter = updateRate;

	while (!m_window.isClosed()) {
		std::chrono::duration<float> deltaTime = (clock::now() - currentTime) * 1'000;
		currentTime = clock::now();
		
		m_playerHead->updateDir();

		if (deltaTime.count() >= updateTimeCounter) {
			float remainingDT = deltaTime.count() - updateTimeCounter;
			updatePlayerAndFruit();
			while (remainingDT >= updateRate) {
				updatePlayerAndFruit();
				remainingDT -= updateRate;
			}

			updateTimeCounter = updateRate - remainingDT;
		}
		else
			updateTimeCounter -= deltaTime.count();

		render();

		m_window.update();
	}
}

void GameSystem::updatePlayerAndFruit()
{
	m_playerHead->update();

	for (int i = 1; i < m_player.size(); i++) {
		m_player[i]->update(m_player[i - 1]->getCurrentDir(), m_player[i - 1]->getPrevDir());
	}

	if (m_fruit.getPosition() == m_playerHead->getPosition()) {
		m_score++;

		if (m_player.size() > 1)
			m_player.back()->updateTexture(engine::ResourceManager::getTexture("assets/textures/player/playerBody.png"));
		m_player.push_back(new Tail(engine::ResourceManager::getTexture("assets/textures/player/playerTail.png"), m_player.back()->getPosition(), m_player.back()->getCurrentDir()));

		m_fruit.updatePosition(m_player);
	}
	else {
		for (int i = 1; i < m_player.size(); i++) {
			if (m_playerHead->getPosition() == m_player[i]->getPosition()) {
				glfwTerminate();
				std::cout << "YOU LOST!\nYOUR SCORE IS: " << m_score << std::endl;
				std::cin.get();
				std::exit(100);
			}
		}
	}
}

void GameSystem::render()
{
	m_window.clear();

	m_board.render();

	m_renderBatch.begin();
	for (auto bodyPart : m_player)
		bodyPart->draw(m_renderBatch);
	m_fruit.draw(m_renderBatch);
	m_renderBatch.end();
	m_renderBatch.renderBatch();
}