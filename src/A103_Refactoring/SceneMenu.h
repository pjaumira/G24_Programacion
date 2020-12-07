#pragma once
#include "Scene.h"

class Menu : public Scene {

public :

	Menu();
	~Menu();

	void gameLoop();
	void Update();
	void Draw();

private : 

	bool controlMusic;
	void SoundToggle();
};