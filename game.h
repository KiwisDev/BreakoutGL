#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>

#include "spriteRenderer.h"
#include "ressourceManager.h"
#include "shader.h"
#include "gameLevel.h"
#include "player.h"
#include "ball.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

class Game {
private:
	GameState state;
	bool keys[1024];
	unsigned int width, height;
	SpriteRenderer* renderer;
	std::vector<GameLevel> levels;
	unsigned int currentLvl;
	Player* player;
	Ball* ball;

	void doCollision();
	Direction collisionDir(glm::vec2 diff);
	void resetLevel();
	void resetPlayer();

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