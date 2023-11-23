#include "brick.h"

Brick::Brick() : GameObject() {
	this->texture = nullptr;
	this->isUndestroyable = false;
	this->isDestroyed = false;
}

Brick::Brick(glm::vec2 pos, glm::vec2 size, Texture2D* texture, float rot, bool undestroyable, glm::vec3 color, glm::vec2 velocity) 
	: GameObject(pos, size, rot, color, velocity) {
	this->texture = texture;
	this->isUndestroyable = undestroyable;
	this->isDestroyed = false;
}

void Brick::draw(SpriteRenderer* renderer) {
	renderer->drawSpite(this->texture, this->position, this->size, this->rotation, this->color);
}
