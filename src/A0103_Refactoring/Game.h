		#pragma once

#include "Utilities.h"
#include "Player.h"
#include "GoldBag.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h> 
#include <SDL_ttf.h>

class Game
{
private:
	GameState _gameState;
	InputData _input;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::vector<Player*> _players;
	std::vector<GoldBags*	> _goldBags;
	float timeDown, totalGameTime;

	MTextures _Textures;
	MRects _Rects;
	TTF_Font* font_timmer = nullptr;
	SDL_Surface* surfTimer = nullptr;
	Mix_Music* soundtrack = nullptr;

public:
	Game();
	~Game();

	void Run();

private:

	void InitSDL();
	void InitMenu();
	void InitGame();

	void UpdateInput();
	void UpdateMenu();
	void UpdateGame();

	void RenderMenu();
	void RenderGame();

	void CloseSDL();
	void DestroyAllTextures();

	void ResetGame();
	void AddPlayer(int texWidth, int texHeight, Player::numPlayer pNum);
	void AddGoldBags();
};