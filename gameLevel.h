#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>

#include "brick.h"

class GameLevel {
private:
	std::vector<Brick> bricks;

public:
	void load(const char* file, unsigned int width, unsigned int height);
	void draw(SpriteRenderer* renderer);
	bool isCompleted;
};

#endif