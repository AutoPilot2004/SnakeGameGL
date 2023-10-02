#pragma once

namespace engine
{
	struct Position
	{
		float x;
		float y;
		float z;
		float w;
	};

	struct Color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};

	struct UV
	{
		float u;
		float v;
	};

	struct Vertex
	{

		Position position;
		Color color;

		UV uv;

		void addPosition(glm::vec4 position) {
			this->position.x = position.x;
			this->position.y = position.y;
			this->position.z = position.z;
			this->position.w = position.w;
		}

		void addColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void addUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
	};
}