#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>

#include "texture2D.h"
#include "spriteRenderer.h"

class GameObject {
public:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 size;
	glm::vec3 color;
	float rotation;

	Texture2D* texture;

	bool isUndestroyable;
	bool isDestroyed;

	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D* texture, float rot = 0.0f, bool undestroyable = false, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void draw(SpriteRenderer* renderer);
};

#endif