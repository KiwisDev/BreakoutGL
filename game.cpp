#include "game.h"

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

const glm::vec2 BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.0f;

Game::Game(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	this->renderer = nullptr;
	this->state = GAME_ACTIVE;
	this->currentLvl = 0;
	this->player = nullptr;
	this->ball = nullptr;

	for (int i = 0; i < 1024; i++) {
		this->keys[i] = false;
	}
}

void Game::init() {
	Shader* shad = RessourceManager::loadShader("sprite", "shaders/vertexSprite.vs", "shaders/fragmentSprite.fs");

	glm::mat4 proj = glm::ortho(0.0f, (float)this->width, (float)this->height, 0.0f, -1.0f, 1.0f);
	shad->use();
	shad->setInt("image", 0);
	shad->setMat4("projection", proj);

	this->renderer = new SpriteRenderer(shad);

	RessourceManager::loadTexture("face", "textures/awesomeface.png", false, true);
	RessourceManager::loadTexture("background", "textures/background.jpg", false, false);
	RessourceManager::loadTexture("brick", "textures/brick.png", false, false);
	RessourceManager::loadTexture("brick_solid", "textures/brick_solid.png", false, false);
	RessourceManager::loadTexture("player", "textures/paddle.png", false, true);

	GameLevel lvlOne; lvlOne.load("levels/levelOne.lvl", this->width, this->height / 2);
	this->levels.push_back(lvlOne);

	glm::vec2 playerPos(this->width / 2.0f - PLAYER_SIZE.x / 2.0f, this->height - PLAYER_SIZE.y);
	this->player = new Player(playerPos, PLAYER_SIZE, RessourceManager::getTexture("player"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	this->ball = new Ball(ballPos, BALL_RADIUS, BALL_VELOCITY, RessourceManager::getTexture("face"));
}

void Game::processInput(float dt) {
	if (this->state == GAME_ACTIVE) {
		float vel = PLAYER_VELOCITY * dt;

		if (this->keys[65]) {
			if (this->player->position.x >= 0.0f) {
				this->player->position.x -= vel;
				if (this->ball->freeze) {
					this->ball->position.x -= vel;
				}
			}
		}

		if (this->keys[68]) {
			if (this->player->position.x <= this->width - this->player->size.x) {
				this->player->position.x += vel;
				if (this->ball->freeze) {
					this->ball->position.x += vel;
				}
			}
		}

		if (this->keys[32]) {
			this->ball->freeze = false;
		}
	}
}

void Game::update(float dt) {
	this->ball->update(dt, width);
	this->doCollision();

	if (this->ball->position.y >= this->height) {
		this->resetLevel();
		this->resetPlayer();
	}
}

void Game::render() {
	if (this->state == GAME_ACTIVE) {
		this->renderer->drawSpite(RessourceManager::getTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(width, height));

		this->levels[this->currentLvl].draw(this->renderer);
		this->player->draw(this->renderer);
		this->ball->draw(this->renderer);
	}
}

void Game::doCollision() {
	glm::vec2 ballCenter(this->ball->position + this->ball->radius);
	std::vector<Brick>* bricks = this->levels[currentLvl].getBricks();
	
	// Check bricks collision
	for (int i = 0; i < bricks->size(); i++) {
		Brick* brick = &bricks->at(i);
		if (!brick->isDestroyed) {
			glm::vec2 halfExtends(brick->size.x / 2.0f, brick->size.y / 2.0f);
			glm::vec2 brickCenter(brick->position.x + halfExtends.x, brick->position.y + halfExtends.y);

			glm::vec2 clamped = glm::clamp(glm::vec2(ballCenter - brickCenter), -halfExtends, halfExtends);
			glm::vec2 closest = brickCenter + clamped;

			glm::vec2 diff(closest - ballCenter);

			if (glm::length(diff) < this->ball->radius) {
				if (!brick->isUndestroyable)
					brick->isDestroyed = true;
				
				Direction dir = collisionDir(diff);

				if (dir == LEFT || dir == RIGHT) {
					this->ball->velocity.x = -this->ball->velocity.x;

					float penetration = this->ball->radius - std::abs(diff.x);
					if (dir == LEFT)
						this->ball->position.x += penetration;
					else
						this->ball->position.x -= penetration;
				}
				else {
					this->ball->velocity.y = -this->ball->velocity.y;

					float penetration = this->ball->radius - std::abs(diff.y);
					if (dir == UP)
						this->ball->position.y -= penetration;
					else
						this->ball->position.y += penetration;
				}
			}
		}
	}

	// Check player collision
	if (!this->ball->freeze) {
		glm::vec2 halfExtends(this->player->size.x / 2.0f, this->player->size.y / 2.0f);
		glm::vec2 playerCenter(this->player->position.x + halfExtends.x, this->player->position.y + halfExtends.y);

		glm::vec2 clamped = glm::clamp(glm::vec2(ballCenter - playerCenter), -halfExtends, halfExtends);
		glm::vec2 closest = playerCenter + clamped;

		glm::vec2 diff(closest - ballCenter);

		if (glm::length(diff) < this->ball->radius) {
			float percent = ((this->ball->position.x + this->ball->radius) - playerCenter.x) / halfExtends.x;

			float strength = 2.0f;
			glm::vec2 oldVel = this->ball->velocity;
			this->ball->velocity.x = BALL_VELOCITY.x * percent * strength;
			this->ball->velocity.y = -1 * std::abs(this->ball->velocity.y);
			this->ball->velocity = glm::normalize(this->ball->velocity) * glm::length(oldVel);
		}
	}
}

Direction Game::collisionDir(glm::vec2 diff) {
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};

	float max = 0.0f;
	int best = -1;
	for (int i = 0; i < 4; i++) {
		float dot = glm::dot(glm::normalize(diff), compass[i]);
		if (dot > max) {
			max = dot;
			best = i;
		}
	}

	return (Direction) best;
}

void Game::resetLevel() {
	switch (this->currentLvl) {
	case 0:
		this->levels[0].load("levels/levelOne.lvl", this->width, this->height / 2);
	}
}

void Game::resetPlayer() {
	this->player->position = glm::vec2(this->width / 2.0f - PLAYER_SIZE.x / 2.0f, this->height - PLAYER_SIZE.y);
	this->ball->reset(glm::vec2(this->player->position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f)), BALL_VELOCITY);
}

Game::~Game() {

}