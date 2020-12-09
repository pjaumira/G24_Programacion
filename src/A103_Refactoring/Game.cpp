#include "Game.h"
#include "Renderer.h"

Game::Game() {
	gameScene = gameState::MENU;
	currentScene = new Menu;
}

Game::~Game()
{
	delete[] currentScene;
}

void Game::Run() {
	while (gameScene != gameState::EXIT) {
		while (SDL_PollEvent(&Renderer::Instance()->event)){
			switch (Renderer::Instance()->event.type) {
			case SDL_QUIT:
				break;
			case SDL_KEYDOWN:
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_ESCAPE) Inputs::Check()->esc = true;

				if (Renderer::Instance()->event.key.keysym.sym == SDLK_w) Inputs::Check()->moveP1Up = true;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_s) Inputs::Check()->moveP1Down = true;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_a) Inputs::Check()->moveP1left = true;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_d) Inputs::Check()->moveP1Right = true;

				if (Renderer::Instance()->event.key.keysym.sym == SDLK_UP) Inputs::Check()->moveP2Up = true;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_DOWN) Inputs::Check()->moveP2Down = true;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_LEFT) Inputs::Check()->moveP2left = true;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_RIGHT) Inputs::Check()->moveP2Right = true;
				break;
			case SDL_KEYUP:
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_ESCAPE) Inputs::Check()->esc = false;

				if (Renderer::Instance()->event.key.keysym.sym == SDLK_w) Inputs::Check()->moveP1Up = false;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_s) Inputs::Check()->moveP1Down = false;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_a) Inputs::Check()->moveP1left = false;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_d) Inputs::Check()->moveP1Right = false;

				if (Renderer::Instance()->event.key.keysym.sym == SDLK_UP) Inputs::Check()->moveP2Up = false;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_DOWN) Inputs::Check()->moveP2Down = false;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_LEFT) Inputs::Check()->moveP2left = false;
				if (Renderer::Instance()->event.key.keysym.sym == SDLK_RIGHT) Inputs::Check()->moveP2Right = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (Renderer::Instance()->event.button.button == SDL_BUTTON_LEFT) { Inputs::Check()->mousePressed = true;}
				break;
			case SDL_MOUSEBUTTONUP:
				if (Renderer::Instance()->event.button.button == SDL_BUTTON_LEFT) { Inputs::Check()->mousePressed = false; }
				break;
			default:
				break;
			}
		}

		switch (currentScene->GetState()) {
		case Scene::SceneState::RUNNING:
			currentScene->gameLoop();
			currentScene->Update();
			currentScene->Draw();
			break;
		case Scene::SceneState::GOTO:
			switch (currentScene->GetGameState()) {
			case Scene::GameState::MENU:
				delete currentScene;
				currentScene = new Play;
				gameScene = gameState::PLAY;
				break;
			case Scene::GameState::GAME:
				delete currentScene;
				currentScene = new Menu;
				gameScene = gameState::MENU;
				break;
			default:
				break;
			}
		case Scene::SceneState::EXIT:
			switch (gameScene) {
			default:
				delete currentScene;
				currentScene = nullptr;
				gameScene = gameState::EXIT;
				break;
			}
		default:
			break;
		}
	}
}

Inputs* Inputs::inputs = nullptr;