#include "Camera2D.h"

namespace engine
{
	Camera2D::Camera2D()
		: m_needsUpdate(true), m_position(0.0f, 0.0f), m_cameraMatrix(1.0f), m_orthoMatrix(1.0f), m_scale(1.0f), m_rotate(0.0f), m_sWidth(500), m_sHeight(500)
	{
		
	}

	Camera2D::~Camera2D()
	{

	}

	void Camera2D::init(int screenWidth, int screenHeight)
	{
		m_sWidth = screenWidth;
		m_sHeight = screenHeight;
		m_orthoMatrix = glm::ortho(0.0f, (float)m_sWidth, 0.0f, (float)m_sHeight, 1.0f, -1.0f);
	}

	void Camera2D::update()
	{
		if (m_needsUpdate) {
			glm::mat4 view(1.0f);
			view = glm::translate(view, glm::vec3(m_sWidth / 2, m_sHeight / 2, -1.0f));
			view = glm::scale(view, glm::vec3(m_scale, m_scale, 0.0f));
			view = glm::translate(view, glm::vec3(-m_position.x, -m_position.y, 0.0f));

			m_cameraMatrix = m_orthoMatrix * view;

			m_needsUpdate = false;
		}
	}

	glm::vec2 Camera2D::screenToWorld(glm::vec2 screenCoords)
	{
		screenCoords.y = m_sHeight - screenCoords.y;
		screenCoords -= glm::vec2(m_sWidth / 2.0f, m_sHeight / 2.0f);
		screenCoords /= m_scale;
		screenCoords += m_position;

		return screenCoords;
	}
}