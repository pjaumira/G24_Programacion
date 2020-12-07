#pragma once

class Scene
{
public:

	Scene();
	~Scene();

	int scoreRecord;

	enum class SceneState { RUNNING, GOTO, EXIT };
	SceneState StateScene;
	SceneState GetState();

	enum class GameState {MENU, GAME,EXIT };
	GameState gameScene;
	GameState GetGameState();

	virtual void gameLoop();
	virtual void update();
	virtual void draw();
};


