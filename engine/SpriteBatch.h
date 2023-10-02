#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>

#include "Vertex.h"

namespace engine
{
	struct Glyph
	{
		GLuint textureID;

		float depth;

		Vertex topLeft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin();
		void end();

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, Color color, float rotation = 0.0f);

		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();

		static bool sortWithTexture(Glyph* a, Glyph* b);

	private:
		GLuint m_vaoID;
		GLuint m_vboID;

		std::vector<Glyph*> m_glyphs;
		glm::vec4 m_localGlyphPositions[4];

		std::map<GLuint, unsigned int> m_renderBatches;

	};
}