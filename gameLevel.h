#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>
#include <fstream>
#include <sstream>

#include "brick.h"
#include "ressourceManager.h"

class GameLevel {
private:
	std::vector<Brick> bricks;

	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int lvlWidht, unsigned int lvlHeight);

public:
	void load(const char* file, unsigned int width, unsigned int height);
	void draw(SpriteRenderer* renderer);
	bool isCompleted();

	std::vector<Brick>* getBricks() { return &bricks; }
};

#endif