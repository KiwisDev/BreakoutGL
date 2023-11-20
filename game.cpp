#include "game.h"

Game::Game(unsigned int width, unsigned int height) {
	this->widht = width;
	this->height = height;
	this->renderer = nullptr;
	this->state = GAME_ACTIVE;

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
}

void Game::processInput(float dt) {

}

void Game::update(float dt) {

}

void Game::render() {
	this->renderer->drawSpite(RessourceManager::getTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

Game::~Game() {

}