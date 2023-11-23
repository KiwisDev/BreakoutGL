#include "gameObject.h"

GameObject::GameObject() {
	this->position = glm::vec2(0.0f);
	this->velocity = glm::vec2(0.0f);
	this->size = glm::vec2(10.0f);
	this->color = glm::vec3(1.0f);
	this->rotation = 0.0f;
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, float rot, glm::vec3 color, glm::vec2 velocity) {
	this->position = pos;
	this->velocity = velocity;
	this->size = size;
	this->color = color;
	this->rotation = rot;
}

void GameObject::draw(SpriteRenderer* renderer) {}