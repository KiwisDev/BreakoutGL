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
	this->doColision();
}

void Game::render() {
	if (this->state == GAME_ACTIVE) {
		this->renderer->drawSpite(RessourceManager::getTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(width, height));

		this->levels[this->currentLvl].draw(this->renderer);
		this->player->draw(this->renderer);
		this->ball->draw(this->renderer);
	}
}

void Game::doColision() {
	glm::vec2 ballCenter(this->ball->position + this->ball->radius);
	std::vector<Brick>* bricks = this->levels[currentLvl].getBricks();
	
	for (int i = 0; i < bricks->size(); i++) {
		Brick* brick = &bricks->at(i);
		if (!brick->isDestroyed) {
			glm::vec2 halfExtends(brick->size.x / 2.0f, brick->size.y / 2.0f);
			glm::vec2 brickCenter(brick->position.x + halfExtends.x, brick->position.y + halfExtends.y);

			glm::vec2 clamped = glm::clamp(glm::vec2(ballCenter - brickCenter), -halfExtends, halfExtends);
			glm::vec2 closest = brickCenter + clamped;

			glm::vec2 diff(closest - ballCenter);

			if (glm::length(diff) < this->ball->radius) {
				if (!brick->isUndestroyable) {
					brick->isDestroyed = true;
				}
			}
		}
	}
}

Game::~Game() {

}