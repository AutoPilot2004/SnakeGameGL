#pragma once

namespace engine
{
	class FPSLimiter
	{
	public:
		FPSLimiter();

		void init(float targetFPS);

		void setMaxFPS(float targetFPS);

		void begin();
		
		//Returns FPS
		float end();

	private:
		void calculateFPS();

	private:
		unsigned int m_startTicks;

		float m_maxFPS;
		float m_frameTime;
		float m_fps;
	};
}