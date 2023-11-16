#pragma once

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

public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void init();
	void processInput(float dt);
	void update(float dt);
	void render();
};