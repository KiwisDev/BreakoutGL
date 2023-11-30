#include "ball.h"

Ball::Ball() : GameObject(){
	this->radius = 12.0f;
	this->freeze = true;
	this->texture = nullptr;
}

Ball::Ball(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D* texture)
	: GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), 0.0f, glm::vec3(1.0f), velocity) {
	this->radius = radius;
	this->texture = texture;
	this->freeze = true;
}

void Ball::update(float dt, unsigned int width) {
	if (!this->freeze) {
		this->position += this->velocity * dt;

		if (this->position.x <= 0.0f) {
			this->velocity.x = -this->velocity.x;
			this->position.x = 0.0f;
		}
		else if (this->position.x + this->size.x >= width) {
			this->velocity.x = -this->velocity.x;
			this->position.x = width - this->size.x;
		}

		if (this->position.y <= 0.0f) {
			this->velocity.y = -this->velocity.y;
			this->position.y = 0.0f;
		}
	}
}

void Ball::draw(SpriteRenderer* renderer) {
	renderer->drawSpite(this->texture, this->position, this->size);
}

void Ball::reset(glm::vec2 pos, glm::vec2 velocity) {
	this->position = pos;
	this->velocity = velocity;
	this->freeze = true;
}