#include "gameObject.h"

GameObject::GameObject() {
	this->position = glm::vec2(0.0f);
	this->velocity = glm::vec2(0.0f);
	this->size = glm::vec2(10.0f);
	this->color = glm::vec3(1.0f);
	this->rotation = 0.0f;

	this->texture = nullptr;

	this->isUndestroyable = false;
	this->isDestroyed = false;
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D* texture, float rot, bool undestroyable, glm::vec3 color, glm::vec2 velocity) {
	this->position = pos;
	this->velocity = velocity;
	this->size = size;
	this->color = color;
	this->rotation = rot;

	this->texture = texture;

	this->isUndestroyable = undestroyable;
	this->isDestroyed = false;
}

void GameObject::draw(SpriteRenderer* renderer) {
	renderer->drawSpite(this->texture, this->position, this->size, this->rotation, this->color):
}