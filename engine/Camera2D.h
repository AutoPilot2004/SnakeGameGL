#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);

		void update();

		glm::vec2 screenToWorld(glm::vec2 screenCoords);

		//Setters
		void setPosition(const glm::vec2& newPosition) { m_position = newPosition; m_needsUpdate = true; }
		void setScale(float newScale) { m_scale = newScale; m_needsUpdate = true; }
		void setRotation(float newRotation) { m_rotate = newRotation; m_needsUpdate = true; }

		//Getters
		inline glm::vec2 getPosition() const { return m_position; }
		inline float getScale() const { return m_scale; }
		inline const glm::mat4& getCameraMatrix() const { return m_cameraMatrix; }
		inline float getRotation() const { return m_rotate; }

	private:
		int m_sWidth, m_sHeight;
		bool m_needsUpdate;
		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;

		float m_scale;
		float m_rotate;
	};
}