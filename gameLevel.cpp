#include "gameLevel.h"
#include <iostream>

void GameLevel::load(const char* file, unsigned int width, unsigned int height) {
	this->bricks.clear();

	std::string line;
	std::ifstream fs(file);
	unsigned int tileCode;
	std::vector<std::vector<unsigned int>> tileData;

	if (fs) {
		while (std::getline(fs, line)) {
			std::istringstream ss(line);
			std::vector<unsigned int> row;

			while (ss >> tileCode) {
				row.push_back(tileCode);
			}

			tileData.push_back(row);
		}
	}

	if (tileData.size() > 0)
		this->init(tileData, width, height);
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int lvlWidht, unsigned int lvlHeight) {
	float h = static_cast<float>(tileData.size());
	float w = static_cast<float>(tileData[0].size());

	std::cout << w << " " << h << std::endl;

	float unit_widht = lvlWidht / w;
	float unit_height = lvlHeight / h;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (tileData[y][x] == 1) {
				glm::vec2 pos(unit_widht * x, unit_height * y);
				glm::vec2 size(unit_widht, unit_height);

				std::cout << "Brick solid " << x << " " << y << std::endl;
				this->bricks.push_back(Brick(pos, size, RessourceManager::getTexture("brick_solid"), 0.0f, true, glm::vec3(0.8f, 0.8f, 0.7f)));
			} else if (tileData[y][x] > 1) {
				glm::vec3 color(1.0f);

				if (tileData[y][x] == 2)
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				else if (tileData[y][x] == 3)
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				else if (tileData[y][x] == 4)
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				else if (tileData[y][x] == 5)
					color = glm::vec3(1.0f, 0.5f, 0.0f);

				glm::vec2 pos(unit_widht * x, unit_height * y);
				glm::vec2 size(unit_widht, unit_height);

				std::cout << "Brick " << x << " " << y << std::endl;
				this->bricks.push_back(Brick(pos, size, RessourceManager::getTexture("brick"), 0.0f, false, color));
			}
		}
	}
}

void GameLevel::draw(SpriteRenderer* renderer) {
	for (Brick& brick : this->bricks) {
		if (!brick.isDestroyed) {
			brick.draw(renderer);
		}
	}
}

bool GameLevel::isCompleted() {
	for (Brick& brick : this->bricks) {
		if (!brick.isUndestroyable && !brick.isDestroyed)
			return false;
		return true;
	}
}