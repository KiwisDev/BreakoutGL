#ifndef BALL_H
#define BALL_H

#include <glm/glm.hpp>

#include "gameObject.h"
#include "texture2D.h"
#include "spriteRenderer.h"

class Ball : public GameObject {
public:
	Texture2D* texture;

	float radius;
	bool freeze;

	Ball();
	Ball(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D* texture);

	void update(float dt, unsigned int width);
	void draw(SpriteRenderer* renderer);
	void reset(glm::vec2 pos, glm::vec2 velocity = glm::vec2(0.0f));
};

#endif BALL_H