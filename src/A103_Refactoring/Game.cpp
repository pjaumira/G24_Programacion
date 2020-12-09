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
				break;
			case SDL_KEYUP:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
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