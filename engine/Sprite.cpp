#include "Sprite.h"
#include "Vertex.h"

#include "ResourceManager.h"

#include <glm/gtc/matrix_transform.hpp>

namespace engine
{
	Sprite::Sprite() : m_vboID(0), m_iboID(0), m_modelMat(1.0f)
	{
	}

	Sprite::~Sprite()
	{
		if (m_vboID != 0) glDeleteBuffers(1, &m_vboID);
		if (m_iboID != 0) glDeleteBuffers(1, &m_iboID);
	}

	void Sprite::init(const std::string& texPath, float x, float y, float width, float height)
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;

		m_texture = ResourceManager::getTexture(texPath);

		if (m_vaoID == 0) {
			glGenVertexArrays(1, &m_vaoID);
		}

		if (m_vboID == 0) {
			glGenBuffers(1, &m_vboID);
		}

		if (m_iboID == 0) {
			glGenBuffers(1, &m_iboID);
		}

		Vertex vertexData[4] = {};

		/*vertexData[0].addPosition(0 - width / 2.0f, 0 - height / 2.0f);
		vertexData[0].addUV(0.0f, 0.0f);

		vertexData[1].addPosition(0 + width - (width / 2.0f), 0 - height / 2.0f);
		vertexData[1].addUV(1.0f, 0.0f);

		vertexData[2].addPosition(0 + width - width / 2.0f, 0 + height - height / 2.0f);
		vertexData[2].addUV(1.0f, 1.0f);

		vertexData[3].addPosition(0 - width / 2.0f, 0 + height - height / 2.0f);
		vertexData[3].addUV(0.0f, 1.0f);*/

		for (int i = 0; i < 4; i++) {
			vertexData[i].addColor(225, 255, 255, 255);
		}

		//vertexData[2].addColor(240, 0, 130, 255);

		unsigned int indexData[6] = {
			0, 1, 2,
			2, 3, 0
		};

		glBindVertexArray(m_vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertexData, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(m_x, m_y, 0.0f));
		model = glm::rotate(model, glm::radians(m_rotate), glm::vec3(0.0f, 0.0f, 1.0f));

		m_modelMat = model;

		glBindTexture(GL_TEXTURE_2D, m_texture.id);

		glBindVertexArray(m_vaoID);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}
}