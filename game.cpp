#include "game.h"

Game::Game(unsigned int width, unsigned int height) {
	this->widht = width;
	this->height = height;
	this->state = GAME_ACTIVE;

	for (int i = 0; i < 1024; i++) {
		this->keys[i] = false;
	}
}

void Game::init() {

}

void Game::processInput(float dt) {

}

void Game::update(float dt) {

}

void Game::render() {

}

Game::~Game() {

}