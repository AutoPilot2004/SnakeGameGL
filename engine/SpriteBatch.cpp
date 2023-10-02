#include "SpriteBatch.h"
#include <algorithm>
#include <glm/gtx/rotate_vector.hpp>

namespace engine
{
	SpriteBatch::SpriteBatch() : m_vboID(0), m_vaoID(0)
	{
		m_localGlyphPositions[0] = { -1.0f, -1.0f, 0.0f, 1.0f };
		m_localGlyphPositions[1] = {  1.0f, -1.0f, 0.0f, 1.0f };
		m_localGlyphPositions[2] = {  1.0f,  1.0f, 0.0f, 1.0f };
		m_localGlyphPositions[3] = { -1.0f,  1.0f, 0.0f, 1.0f };
	}

	SpriteBatch::~SpriteBatch()
	{

	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin()
	{
		m_renderBatches.clear();

		for (auto glyph : m_glyphs)
			delete glyph;

		m_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		std::sort(m_glyphs.begin(), m_glyphs.end(), sortWithTexture);
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, Color color, float rotation /*= 0.0f*/)
	{
		Glyph* newGlyph = new Glyph;
		newGlyph->depth = depth;
		newGlyph->textureID = textureID;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(destRect.x, destRect.y, depth));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(destRect.z / 2.0f, -destRect.w / 2.0f, 1.0f));
		
		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.addPosition(model * m_localGlyphPositions[0]);
		newGlyph->bottomLeft.addUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.addPosition(model * m_localGlyphPositions[1]);
		newGlyph->bottomRight.addUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.addPosition(model * m_localGlyphPositions[2]);
		newGlyph->topRight.addUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.addPosition(model * m_localGlyphPositions[3]);
		newGlyph->topLeft.addUV(uvRect.x, uvRect.y + uvRect.w);

		m_glyphs.push_back(newGlyph);
	}

	void SpriteBatch::renderBatch()
	{
		unsigned int offset = 0;

		glBindVertexArray(m_vaoID);

		glActiveTexture(GL_TEXTURE0);

		for (auto it = m_renderBatches.begin(); it != m_renderBatches.end(); it++) {
			glBindTexture(GL_TEXTURE_2D, it->first);

			glDrawArrays(GL_TRIANGLES, offset, it->second);
			offset += it->second;
		}
	}

	void SpriteBatch::createRenderBatches()
	{
		if (m_glyphs.empty()) return;

		std::vector<Vertex> vertices;

		vertices.resize(m_glyphs.size() * 6);

		int cv = 0;  // index of vertices

		for (int cg = 0; cg < m_glyphs.size(); cg++) {
			m_renderBatches[m_glyphs[cg]->textureID] += 6;

			vertices[cv++] = m_glyphs[cg]->bottomLeft;
			vertices[cv++] = m_glyphs[cg]->bottomRight;
			vertices[cv++] = m_glyphs[cg]->topRight;

			vertices[cv++] = m_glyphs[cg]->topRight;
			vertices[cv++] = m_glyphs[cg]->topLeft;
			vertices[cv++] = m_glyphs[cg]->bottomLeft;
		}

		glBindVertexArray(m_vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
	}

	void SpriteBatch::createVertexArray()
	{

		if (m_vaoID == 0)
			glGenVertexArrays(1, &m_vaoID);

		if (m_vboID == 0)
			glGenBuffers(1, &m_vboID);

		glBindVertexArray(m_vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, uv));
	}

	bool SpriteBatch::sortWithTexture(Glyph* a, Glyph* b)
	{
		return (a->textureID < b->textureID);
	}
}