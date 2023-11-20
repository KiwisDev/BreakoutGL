#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>

#include "spriteRenderer.h"
#include "ressourceManager.h"
#include "shader.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game {
private:
	GameState state;
	bool keys[1024];
	unsigned int widht, height;
	SpriteRenderer* renderer;

public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void init();
	void processInput(float dt);
	void update(float dt);
	void render();

	void setKey(int index, bool val) {
		keys[index] = val;
	}
};

#endif