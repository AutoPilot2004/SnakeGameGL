#pragma once
#include "BodyPart.h"
#include <engine/GLTexture.h>

class Tail : public BodyPart
{
public:
	Tail(engine::GLTexture texture, glm::vec2 posOfFront, Direction dirOfFront);
	~Tail() override;

private:

};