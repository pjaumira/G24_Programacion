#pragma once

#include "SceneMenu.h"
#include "ScenePlay.h"
#include "Types.h"

class Game {

public :

	Game();
	~Game();

	enum class gameState {MENU, PLAY};
	gameState gameScene;

	Scene* currentScene;

	void Run();

private :

	int score;

};


