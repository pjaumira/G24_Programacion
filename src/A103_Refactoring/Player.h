#include "Types.h"

class Player {

private:

	int textWidth, textHeight, frameWidth, frameHeight;

public:

	Player();
	~Player();

	Vec2 playerPosition;

	int frameTime;
	int scorePlayer;

	void gameLoop();
	void Update();
	void Draw();
};