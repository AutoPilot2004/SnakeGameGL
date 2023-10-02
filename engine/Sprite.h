#pragma once
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

#include "GLTexture.h"

namespace engine
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(const std::string& texPath, float x, float y, float width, float height);

		void draw();
		
		//Setters
		void setRotation(float newRotation) { m_rotate = newRotation; }

		//Getters
		inline glm::mat4 getModelMatrix() const { return m_modelMat; }
		inline float getRotation() const { return m_rotate; }

	private:
		GLuint m_vaoID;
		GLuint m_vboID;
		GLuint m_iboID;

		float m_x, m_y;
		float m_width, m_height;
		float m_rotate;

		GLTexture m_texture;

		glm::mat4 m_modelMat;
	};
}