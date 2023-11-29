#include "player.h"

Player::Player() : GameObject() {
	this->texture = nullptr;
}

Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D* texture, float rot, glm::vec3 color, glm::vec2 velocity)
	: GameObject(pos, size, rot, color, velocity) {
	this->texture = texture;
}

void Player::draw(SpriteRenderer* renderer) {
	renderer->drawSpite(this->texture, this->position, this->size, this->rotation, this->color);
}
