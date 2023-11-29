#ifndef BRICK_H
#define BRIDK_H

#include "gameObject.h"
#include "texture2D.h"

class Brick : public GameObject {
public:
	Texture2D* texture;

	bool isUndestroyable;
	bool isDestroyed;

	Brick();
	Brick(glm::vec2 pos, glm::vec2 size, Texture2D* texture, float rot = 0.0f, bool undestroyable = false, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	void draw(SpriteRenderer* renderer);
};

#endif