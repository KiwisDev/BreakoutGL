#include "game.h"

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

const glm::vec2 BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.0f;

Game::Game(unsigned int width, unsigned int height) {
	this->widht = width;
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

	glm::mat4 proj = glm::ortho(0.0f, (float)this->widht, (float)this->height, 0.0f, -1.0f, 1.0f);
	shad->use();
	shad->setInt("image", 0);
	shad->setMat4("projection", proj);

	this->renderer = new SpriteRenderer(shad);

	RessourceManager::loadTexture("face", "textures/awesomeface.png", false, true);
	RessourceManager::loadTexture("background", "textures/background.jpg", false, false);
	RessourceManager::loadTexture("brick", "textures/brick.png", false, false);
	RessourceManager::loadTexture("brick_solid", "textures/brick_solid.png", false, false);
	RessourceManager::loadTexture("player", "textures/paddle.png", false, true);

	GameLevel lvlOne; lvlOne.load("levels/levelOne.lvl", this->widht, this->height / 2);
	this->levels.push_back(lvlOne);

	glm::vec2 playerPos(this->widht / 2.0f - PLAYER_SIZE.x / 2.0f, this->height - PLAYER_SIZE.y);
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
			if (this->player->position.x <= this->widht - this->player->size.x) {
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
	this->ball->update(dt, widht);
}

void Game::render() {
	if (this->state == GAME_ACTIVE) {
		this->renderer->drawSpite(RessourceManager::getTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(widht, height));

		this->levels[this->currentLvl].draw(this->renderer);
		this->player->draw(this->renderer);
		this->ball->draw(this->renderer);
	}
}

Game::~Game() {

}