#pragma once

#include "Scene.h"
#include "Player.h"
#include "goldBag.h"

class Play : public Scene {

public : 

	Play();
	~Play();

	Player* P1;
	Player* P2;

	//Hud* hud;
	Collisions coll;
	GoldBag* goldbag;

	float timer;
};