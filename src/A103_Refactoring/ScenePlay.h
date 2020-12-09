#pragma once

#include "Scene.h"
#include "Constants.h"
#include "Player.h"
#include "goldBag.h"
#include "Collisions.h"
#include "Hud.h"
#include "time.h"

class Play : public Scene {

public : 

	Play();
	~Play();

	Player* P1;
	Player* P2;

	Hud* hud;
	Collisions coll;
	GoldBag* goldbag;

	float timer;
	int textWidth, textHeight, frameWidth, frameHeight;
	enum class gameStates { RUNNING, GAME_OVER};

	void gameLoop();
	void Update();
	void Draw();
};