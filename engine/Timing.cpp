#include "Timing.h"

#include <GLFW/glfw3.h>

namespace engine
{
	FPSLimiter::FPSLimiter()
	{
		
	}
	void FPSLimiter::init(float targetFPS)
	{
		setMaxFPS(targetFPS);
	}

	void FPSLimiter::setMaxFPS(float targetFPS)
	{
		m_maxFPS = targetFPS;
	}

	void FPSLimiter::begin()
	{
		m_startTicks = glfwGetTime() * 1000;
	}

	//Returns FPS
	float FPSLimiter::end()
	{
		calculateFPS();

		return m_fps;
	}

	void FPSLimiter::calculateFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;
		static float currentTicks = glfwGetTime() * 1000;
		static float prevTicks;

		prevTicks = currentTicks;

		currentTicks = glfwGetTime() * 1000;

		m_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

		int count;

		currentFrame++;

		if (currentFrame < NUM_SAMPLES) {
			count = currentFrame;
		}
		else {
			count = NUM_SAMPLES;
		}

		float frameTimeAverage = 0;

		for (int i = 0; i < count; i++) {
			frameTimeAverage += frameTimes[i];
		}

		frameTimeAverage /= count;

		if (frameTimeAverage > 0) {
			m_fps = 1000.0f / frameTimeAverage;
		}
		else {
			m_fps = 60.0f;
		}
	}
}