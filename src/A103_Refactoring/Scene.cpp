#include "Scene.h"
#include "Renderer.h"

Scene::Scene() {
	StateScene = SceneState::RUNNING;
	gameScene = GameState::MENU;
}

Scene::GameState Scene::GetGameState() { return gameScene;}

Scene::SceneState Scene::GetState() { return StateScene;}

void Scene::Draw(){ Renderer::Instance()->Clear();}